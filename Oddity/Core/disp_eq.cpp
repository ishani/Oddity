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

struct EffectDataEQ
{
  Fix16 amplitude, grade;
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataEQ) < Constants::MemoryPool, "EffectDataEQ too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void eq_init(FXState& state)
{
  EffectDataEQ* data = (EffectDataEQ*)state.store;
  
  data->amplitude = 17.0f;
  data->grade = 0.5f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool eq_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataEQ* data = (EffectDataEQ*)state.store;

  output.clear();

  DIAL_ADJUST(2, data->amplitude, 0.35f, fix16_zero, 20.0f);
  DIAL_ADJUST(1, data->grade, 0.025f, fix16_zero, 2.0f);


  Fix16 pT = fix16_mul(fix16_from_int(state.counter), fix16_from_float(0.08f));
  Fix16 pY = fix16_mul(fix16_from_int(state.counter), fix16_from_float(0.03f));

  byte r, g;
  Fix16 colDelta(0.125f);

  for (int32_t x=0; x<Constants::FrameWidth; x++)
  {
    Fix16 pX = fix16_mul(fix16_from_int(x), fix16_from_float(0.3f));
    pX += pT;

    Fix16 row = Perlin2(pX, pY);
    row *= data->amplitude;


    int rowInt = row.asInt();
    if (rowInt < 0)
      rowInt = -rowInt;
    if (rowInt > 8)
      rowInt = 8;

    Fix16 col = data->grade;
    
    FullSpectrum(col, r, g);
    setLED(output.frame, x, 8, r, g);

    for (int32_t y=0; y<rowInt; y++)
    {
      FullSpectrum(col, r, g);
      setLED(output.frame, x, 8 - y, r, g);
      setLED(output.frame, x, 8 + y, r, g);

      col += colDelta;
    }
  }

  return true;
}