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

enum { NumBalls = 3 };
struct EffectDataMeta
{
  Fix16 step, phase;
  Fix16 offset, spool;
  P2 metaballPos[NumBalls];
  Fix16 metaballSize[NumBalls];
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataMeta) < Constants::MemoryPool, "EffectDataMeta too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void meta_init(FXState& state)
{
  EffectDataMeta* data = (EffectDataMeta*)state.store;

  data->offset = 1.8f;
  data->spool = 0.045f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool meta_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataMeta* data = (EffectDataMeta*)state.store;

  output.clear();


  DIAL_ADJUST(1, data->spool, 0.005f, -0.2f, 0.2f);
  DIAL_ADJUST(2, data->offset, 0.1f, -4.0f, 4.0f);


  data->step += data->spool;
  data->phase += data->spool * 0.5f;

  Fix16 offset = 0.0f;
  for (int mb=0; mb<NumBalls; mb++)
  {
    Fix16 dist = Fix16(5.0f) + data->phase.cosV(offset) * 5.0f;

    data->metaballPos[mb].x = Fix16(8.0f) + data->step.cosV(offset) * dist;
    data->metaballPos[mb].y = Fix16(8.0f) + data->step.sinV(offset) * dist;
    
    data->metaballSize[mb] = Fix16(6.0f) + ((Fix16(fix16_pt_five) + data->step.cosMV(0.5f, -offset)) * 7.0f);

    offset += data->offset;
  }

  Fix16 divZeroFudge(0.001f);

  byte r, g;
  for (int y=0; y<Constants::FrameHeight; y++)
  {
    for (int x=0; x<Constants::FrameWidth; x++)
    {
      Fix16 fx((float)x), fy((float)y);

      Fix16 force = fix16_zero;

      for (int mb=0; mb<NumBalls; mb++)
      {
        Fix16 dist = (data->metaballSize[mb] * data->metaballSize[mb]) / (DistanceBetweenSq(fx, fy, data->metaballPos[mb].x, data->metaballPos[mb].y) + divZeroFudge);

        force += dist;
      }

      force = force.sqrt();

      if (force > 5.0f)
        force = 5.0f;
      if (force < 0.0f)
        force = 0.0f;
      {
        Fix16 tn = force * 0.20f;
        tn *= tn;

        BlackEdgeSpectrum(tn, r, g);

        setLED(output.frame, x, y, r, g);
      }
    }
  }

  return true;
}