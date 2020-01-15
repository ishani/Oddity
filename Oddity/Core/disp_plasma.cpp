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

struct EffectDataPlasma
{
  Fix16 step;
  Fix16 attractorScales[4];

  Fix16 speed;

  Fix16 tweak1, tweak2;

  bool mutations[16];
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataPlasma) < Constants::MemoryPool, "EffectDataPlasma too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void plasma_init(FXState& state)
{
  EffectDataPlasma* data = (EffectDataPlasma*)state.store;

  data->step = (fix16_t)state.rng.genUInt32(0, 0xffffff);

  data->speed = 0.4f;

  for (int i=0; i<16; i++)
    data->mutations[i] = state.rng.genBool();

  for (int i=0; i<4; i++)
    data->attractorScales[i] = (fix16_t)state.rng.genUInt32(0, 0xfffff);

  data->tweak1 = 0.1f;
  data->tweak2 = 0.1f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool plasma_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataPlasma* data = (EffectDataPlasma*)state.store;

  DIAL_ADJUST(1, data->tweak1, 0.01f, fix16_zero, fix16_one);
  DIAL_ADJUST(2, data->tweak2, 0.01f, fix16_zero, fix16_one);

  byte r, g;
  Fix16 mid(8.0f);

  Fix16 tx1, ty1, tx2, ty2;

  Fix16 XM1 = data->step.sinMV(0.3f, 3.0f) * data->attractorScales[0];
  Fix16 YM1 = data->step.sinMV(0.1f, 2.0f) * data->attractorScales[1];
  Fix16 XM2 = data->step.cosMV(0.2f, -3.0f) * data->attractorScales[2];
  Fix16 YM2 = data->step.cosMV(0.05f, -5.0f) * data->attractorScales[3];

  tx1 = mid + (data->step.sinV(-0.25f) * XM1);
  ty1 = mid + (data->step.cosV(0.1f) * YM1);
  tx1 = mid + (data->step.sinMV(-0.5f, 4.0f) * XM2);
  ty1 = mid + (data->step.cosV(0.1f) * YM2);

  for (int y=0; y<Constants::FrameHeight; y++)
  {
    for (int x=0; x<Constants::FrameWidth; x++)
    {
      Fix16 fx((float)x), fy((float)y);

      fx += fx.sinMV(0.3f, YM1);
      fy += fy.cosMV(0.3f, XM2);

      Fix16 dist1 = DistanceBetween(fx, fy, tx1, ty1);
      Fix16 dist2 = DistanceBetween(fx, fy, tx2, ty2);

      Fix16 tn = Fix16::atan2(dist1, dist2) * ((data->step.cosM(0.25f) + 2.0f) * 0.8f);

      tn += data->step * 0.4f;

      tn += fx.cosMV(data->tweak1, YM2) * (data->step.sinMV(data->tweak1, 25.0f) * 0.3f);
      tn -= fy.sinMV(data->tweak2, XM1) * (data->step.cosMV(data->tweak2, 15.0f) * 0.3f);

      FullSpectrum(tn, r, g);
      setLED(output.frame, x, y, r, g);
    }
  }

  data->step += 0.1f;

  return true;
}