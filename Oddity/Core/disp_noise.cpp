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

struct EffectDataNoise
{
  Fix16 step, phase, stepSpeed, phaseSpeed;
  Fix16 attractorScales[4];
  bool  mutations[16];
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataNoise) < Constants::MemoryPool, "EffectDataNoise too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void noise_init(FXState& state)
{
  EffectDataNoise* data = (EffectDataNoise*)state.store;

  data->step = (fix16_t)state.rng.genUInt32(0, 0xffff);
  data->phase = (fix16_t)state.rng.genUInt32(0, 0xffff);

  data->stepSpeed = 0.03f;
  data->phaseSpeed = 0.01f;

  for (int i=0; i<16; i++)
    data->mutations[i] = state.rng.genBool();

  for (int i=0; i<4; i++)
    data->attractorScales[i] = (fix16_t)state.rng.genUInt32(0, 0xfffff);

}


// ---------------------------------------------------------------------------------------------------------------------
bool noise_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataNoise* data = (EffectDataNoise*)state.store;

  DIAL_ADJUST(1, data->stepSpeed, 0.001f, fix16_neg_one, fix16_one);
  DIAL_ADJUST(2, data->phaseSpeed, 0.001f, fix16_zero, 0.08f);

  output.clear();

  Fix16 _x, _y, tx, ty, off(0.1f), pr;

  data->step += data->stepSpeed;
  data->phase += data->phaseSpeed;

  off += (data->step.cosM(0.5f) + 1.0f) * 0.04f;

  Fix16 _cos = data->step.cosM(0.25f);
  Fix16 _sin = data->step.sinM(0.25f);

  tx = 0.0f;
  ty = 0.0f;

  byte r, g;
  _y = ty;
  for (int16_t y=0; y<Constants::FrameHeight; y++)
  {
    for (int16_t x=0; x<Constants::FrameWidth; x++)
    {
      Fix16 __x = (_x * _cos) - (_y * _sin);
      Fix16 __y = (_x * _sin) + (_y * _cos);

      pr = Perlin2(__x + data->step, __y - data->step) + fix16_one + data->phase;

      BlackEdgeSpectrum(pr, r, g);
      setLED(output.frame, x, y, r, g);

      _x += off;
    }

    _x = tx;
    _y += off;
  }

  return true;
}