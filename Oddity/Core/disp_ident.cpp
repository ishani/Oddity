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

struct P2
{
  Fix16 x, y;
};

#define RAINDROPS 15
struct EffectDataIdent
{
  TextScroller texto;

  P2    starPt[RAINDROPS];
  Fix16 starVel[RAINDROPS];

  void spawn(FXState& state, int16_t index)
  {
    starPt[index].x = fix16_mul(fix16_from_int(state.rng.genUInt32(1, 30)), fix16_from_float(-1.0f));
    starPt[index].y = fix16_from_int(state.rng.genUInt32(0, 16));

    starVel[index] = fix16_mul(fix16_from_int(state.rng.genUInt32(3, 10)), fix16_from_float(0.06f));
  }

  Fix16 waveinc, wavesize;
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataIdent) < Constants::MemoryPool, "EffectDataIdent too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void ident_init(FXState& state)
{
  EffectDataIdent* data = (EffectDataIdent*)state.store;

  data->texto.Init(" .. ODDITY  @  Kinetica Art Fair 2013!  .. ");

  for (uint16_t i=0; i<RAINDROPS; i++)
  {
    data->spawn(state, i);
  }

  data->waveinc = 0.025f;
  data->wavesize = 4.0f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool ident_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataIdent* data = (EffectDataIdent*)state.store;

  DIAL_ADJUST(1, data->waveinc, 0.01f, 0.0f, 0.08f);
  DIAL_ADJUST(2, data->wavesize, 0.1f, 0.0f, 8.0f);

  output.clear();

  Fix16 vel(0.5f);

  for (uint16_t i=0; i<RAINDROPS; i++)
  {
    data->starPt[i].x += data->starVel[i];

    //Fix16 c = (data->starVel[i] * vel);

    setLED(output.frame, data->starPt[i].x.asInt(), data->starPt[i].y.asInt(), 0, 3, true);
    setLED(output.frame, data->starPt[i].x.asInt() - 1, data->starPt[i].y.asInt(), 0, 1, true);

    if (data->starPt[i].x > 16.0f)
    {
      data->spawn(state, i);
    }
  }

  data->texto.Render(output.frame, Green, data->waveinc, data->wavesize);

  return true;
}