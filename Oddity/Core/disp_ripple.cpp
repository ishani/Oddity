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

struct EffectDataRipple
{
  enum
  {
    Width = Constants::FrameWidth + 2,
    Height = Constants::FrameHeight + 2,
    BufferSize = (Width * Height)
  };

  Fix16     buffer[BufferSize * 3];
  Fix16*    source;
  Fix16*    dest;
  Fix16*    velocity;

  Fix16     droptime;
  Fix16     waverate;
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataRipple) < Constants::MemoryPool, "EffectDataRipple too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void ripple_init(FXState& state)
{
  EffectDataRipple* data = (EffectDataRipple*)state.store;
  
  for(int i = 0; i < EffectDataRipple::BufferSize * 2; ++i)
  {
    data->buffer[i] = fix16_zero;
  }
  data->source = data->buffer;
  data->dest = &data->buffer[EffectDataRipple::BufferSize];
  data->velocity = &data->buffer[EffectDataRipple::BufferSize * 2];
  data->droptime = fix16_one;

  data->waverate = 50.0f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool ripple_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataRipple* data = (EffectDataRipple*)state.store;

  
  DIAL_ADJUST(1, data->waverate, fix16_pt_five, 10.0f, 80.0f);

  data->droptime -= 0.01f;
  if (data->droptime < fix16_zero)
  {
    int32_t newDropX = state.rng.genUInt32(2, 14);
    int32_t newDropY = state.rng.genUInt32(2, 14);

    data->source[(newDropY * EffectDataRipple::Width) + newDropX] += 3.0f;

    data->source[(newDropY * EffectDataRipple::Width) + newDropX - 1] += fix16_one;
    data->source[(newDropY * EffectDataRipple::Width) + newDropX + 1] += fix16_one;

    data->source[((newDropY - 1) * EffectDataRipple::Width) + newDropX] += fix16_one;
    data->source[((newDropY + 1) * EffectDataRipple::Width) + newDropX] += fix16_one;

    data->source[((newDropY - 1) * EffectDataRipple::Width) + newDropX - 1] += fix16_pt_five;
    data->source[((newDropY + 1) * EffectDataRipple::Width) + newDropX - 1] += fix16_pt_five;
    data->source[((newDropY - 1) * EffectDataRipple::Width) + newDropX + 1] += fix16_pt_five;
    data->source[((newDropY + 1) * EffectDataRipple::Width) + newDropX + 1] += fix16_pt_five;

    data->droptime = Fix16((int16_t)state.rng.genUInt32(2, 16)) * fix16_from_float(0.1f);
  }

  output.clear();

  Fix16 mulFour = fix16_from_float(4.0f);
  Fix16 c2 = data->waverate;
  Fix16 recpH2 = fix16_from_float(0.75f);
  Fix16 tStep = fix16_from_float(0.01f);
  Fix16 fadeF = fix16_from_float(0.99f);

  if(input.dialChange[2] != 0)
  {
    data->source[(13 * EffectDataRipple::Width) + 5] += (input.dialChange[2] * 0.2f);
    data->source[(13 * EffectDataRipple::Width) + 6] += (input.dialChange[2] * 0.6f);
    data->source[(13 * EffectDataRipple::Width) + 7] += (input.dialChange[2] * 1.6f);

    data->source[(13 * EffectDataRipple::Width) + 8] += (input.dialChange[2] * 1.8f);
    data->source[(13 * EffectDataRipple::Width) + 9] += (input.dialChange[2] * 1.8f);

    data->source[(13 * EffectDataRipple::Width) + 10] += (input.dialChange[2] * 1.6f);
    data->source[(13 * EffectDataRipple::Width) + 11] += (input.dialChange[2] * 0.6f);
    data->source[(13 * EffectDataRipple::Width) + 12] += (input.dialChange[2] * 0.2f);

    data->droptime = 2.0f;
  }

  for(int y = 1; y < EffectDataRipple::Height - 1; y++)
  {
    for(int x = 1; x < EffectDataRipple::Width - 1; x++) 
    {
      Fix16 smoothed;
      smoothed  = data->source[(y * EffectDataRipple::Width) + x + 1];   // x+1, y
      smoothed += data->source[(y * EffectDataRipple::Width) + x - 1];   // x-1, y
      smoothed += data->source[((y + 1) * EffectDataRipple::Width) + x]; // x, y+1
      smoothed += data->source[((y - 1) * EffectDataRipple::Width) + x]; // x, y-1
      
      smoothed -= data->source[(y * EffectDataRipple::Width) + x] * mulFour;

      smoothed *= c2;
      smoothed *= recpH2;


      data->velocity[(y * EffectDataRipple::Width) + x] += smoothed * tStep;

      Fix16 newVal = data->source[(y * EffectDataRipple::Width) + x] + (data->velocity[(y * EffectDataRipple::Width) + x] * tStep);
      newVal *= fadeF;

      data->dest[(y * EffectDataRipple::Width) + x] = newVal;


      newVal *= 3.0f;

      if (newVal < fix16_neg_one)
        newVal = fix16_neg_one;

      newVal += fix16_one;
      newVal *= fix16_pt_five;

      if (newVal > fix16_one)
        newVal = fix16_one;


      byte r, g;
      GBRSpectrum(newVal, r, g);

      setLED(output.frame, x-1, y-1, r, g, false);
    }
  }

  for(int q = 0; q < EffectDataRipple::BufferSize; q++) 
    data->source[q] = data->dest[q];

  return true;
}