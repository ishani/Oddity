/*
__    ___ __       
____  ____/ /___/ (_) /___  __
/ __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
/ /_/ / /_/ / /_/ / / /_/ /_/ / 
\____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
/____/   
*/

#include "oddity.h"
#include "vfx.h"
#include "lookup_flame.h"

struct EffectDataFlame
{
  enum
  {
    CoalWidth = Constants::FrameWidth - 2,
    CoalHeight = 3,
    Width = Constants::FrameWidth,
    Height = Constants::FrameHeight,
    BufferHeight = Constants::FrameHeight + CoalHeight,
    BufferSize = (Width * BufferHeight)
  };

  uint8_t buffer[BufferSize * 2];
  int frontBuffer;
  int backBuffer;

  int time;

  Fix16 noiseTimeScale;
  Fix16 noiseXScale;
  Fix16 decay;

  bool cswap;
};

uint8_t* frontBuffer;
uint8_t* backBuffer;

#ifdef _MSC_VER
static_assert(sizeof(EffectDataFlame) < Constants::MemoryPool, "EffectDataFlame too big for global memory pool");
#endif // _MSC_VER


// ---------------------------------------------------------------------------------------------------------------------
void flame_init(FXState& state)
{
  EffectDataFlame* data = (EffectDataFlame*)state.store;

  for(int i = 0; i < EffectDataFlame::BufferSize * 2; ++i)
  {
    data->buffer[i] = 0;
  }

  backBuffer = data->buffer;
  frontBuffer = &data->buffer[EffectDataFlame::BufferSize];

  data->time = 0;

  data->noiseTimeScale = 0.1f;
  data->noiseXScale = 0.5f;
  data->decay = 8.2f;

  data->cswap = false;
}

// ---------------------------------------------------------------------------------------------------------------------
bool flame_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataFlame* data = (EffectDataFlame*)state.store;

  // Inputs.
  //
  if(input.dialChange[1] != 0)
  {
    data->decay += (input.dialChange[1] * 0.05f);
  }
  if(input.dialChange[2] != 0)
  {
    data->cswap = !data->cswap;
  }

  // Coals.
  for(int y = EffectDataFlame::BufferHeight - EffectDataFlame::CoalHeight - 1; y < EffectDataFlame::BufferHeight; ++y)
  {  
    for(int x = (EffectDataFlame::Width - EffectDataFlame::CoalWidth) / 2 ; x < EffectDataFlame::Width - (EffectDataFlame::Width - EffectDataFlame::CoalWidth) / 2; ++x)
    { 
      Fix16 noise = Perlin3(x * data->noiseXScale, y * 0.5f, data->time * data->noiseTimeScale) + 0.5f;
      int coalValue = fix16_to_int(noise * 400.0f);
      backBuffer[y * EffectDataFlame::Width + x] = (coalValue < 255 ? coalValue : 255);
    }
  }
  data->time++;

  // Flame.
  //
  uint8_t p1, p2, p3, p4, p5, p6, p7;
  int u, d, l, r;

  for(int x = 0; x < EffectDataFlame::Width; ++x)
  {
    l = x == 0 ? 0 : x - 1;
    r = x == EffectDataFlame::Width - 1 ? EffectDataFlame::Width - 1 : x + 1;

    for(int y = 1; y < EffectDataFlame::BufferHeight - 1; ++y)
    { 
      u = y == 0 ? 0 : y - 1;
      d = y == EffectDataFlame::BufferHeight - 1 ? EffectDataFlame::BufferHeight : y + 1;

      // p1 dest p5
      // p2 src  p6
      // p3 p4   p7

      p1 = backBuffer[u * EffectDataFlame::Width + l ];
      p2 = backBuffer[y * EffectDataFlame::Width + l ];
      p3 = backBuffer[d * EffectDataFlame::Width + l ];

      p4 = backBuffer[d * EffectDataFlame::Width + x ];

      p5 = backBuffer[u * EffectDataFlame::Width + r ];
      p6 = backBuffer[y * EffectDataFlame::Width + r ];
      p7 = backBuffer[d * EffectDataFlame::Width + r ];

      int src = backBuffer[y * EffectDataFlame::Width + x ];

      int sum = src + p1 + p2 + p3 + p4 + p5 + p6 + p7;
      Fix16 result = fix16_from_int(sum);

      result /= data->decay; //8.3f;

      const Fix16 maxValue((int16_t)255);
      result = (result < maxValue ? result : maxValue);
      frontBuffer[(y - 1) * EffectDataFlame::Width + x] = fix16_to_int(result);
    }
  }

  // Cooling.
  //
  for(int i = 0; i < EffectDataFlame::Width * EffectDataFlame::Height; ++i)
  {
    int adjusted = (int)frontBuffer[i] - (int)coolingMap[i] / 4;
    frontBuffer[i] = adjusted > 0 ? adjusted : 0;
  }

  // Draw.
  for(int x = 0; x < EffectDataFlame::Width; ++x)
  {
    for(int y = 0; y < EffectDataFlame::Height; ++y)
    { 
      int index = frontBuffer[y * EffectDataFlame::Width + x];
      index = index >> 3;  
      setLED(output.frame, x, y, 
        data->cswap ? Gr[index] : Rr[index], 
        data->cswap ? Rr[index] : Gr[index]);
    }
  }

  // Flip buffer.
  uint8_t* front = frontBuffer;
  frontBuffer = backBuffer;
  backBuffer = front;

  return true;
}
