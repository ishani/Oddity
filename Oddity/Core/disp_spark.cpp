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

enum { NumParticles = 6 };
struct EffectDataSpark
{
  P2 particlePos[NumParticles];
  P2 particleVel[NumParticles];
  int TTL[NumParticles];
  bool alive[NumParticles];
  Fix16 ex, ey;
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataSpark) < Constants::MemoryPool, "EffectDataSpark too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void spark_init(FXState& state)
{
  EffectDataSpark* data = (EffectDataSpark*)state.store;

  for (int i=0; i<NumParticles; i++)
    data->alive[i] = false;

  data->ex = 7.5f;
  data->ey = 5.5f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool spark_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataSpark* data = (EffectDataSpark*)state.store;

  output.fade(1);

  Fix16 boundMin(0.0f), boundMax(15.0f), invert(-0.7f), decay(0.98f), invertDecayed(-0.8f), vel(0.5f);

  DIAL_ADJUST(1, data->ex, 0.5f, fix16_zero, boundMax);
  DIAL_ADJUST(2, data->ey, 0.5f, fix16_zero, boundMax);


  setLED(output.frame, data->ex.asInt(), data->ey.asInt(), 4, 0);


  int spawnPerFrame = 2;

  for (int i=0; i<NumParticles; i++)
  {
    if (!data->alive[i])
    {
      spawnPerFrame --;
      if (spawnPerFrame > 0)
      {
        data->particlePos[i].x = data->ex;
        data->particlePos[i].y = data->ey;


        data->particleVel[i].x = Fix16(-2.0f) + fix16_mul(fix16_from_int(state.rng.genUInt32(0, 40)), fix16_from_float(0.1f));
        data->particleVel[i].y = Fix16(-2.0f) + fix16_mul(fix16_from_int(state.rng.genUInt32(0, 40)), fix16_from_float(0.1f));

        float asa = data->particleVel[i].x.asFloat();
        
        if (state.rng.genBool())
          data->particleVel[i].x *= fix16_neg_one;

        data->particleVel[i].y *= invert;

        data->alive[i] = true;
        data->TTL[i] = state.rng.genUInt32(60, 120);
      }
    }
    else
    {
      data->particlePos[i].x += data->particleVel[i].x;
      data->particlePos[i].y += data->particleVel[i].y;

      {
        if (data->particlePos[i].x > boundMax)
        {
          data->particlePos[i].x = boundMax;
          data->particleVel[i].x *= invert;
        }
        if (data->particlePos[i].y > boundMax)
        {
          data->particlePos[i].y = boundMax;
          data->particleVel[i].y *= invertDecayed;
        }
        if (data->particlePos[i].x < boundMin)
        {
          data->particlePos[i].x = boundMin;
          data->particleVel[i].x *= invert;
        }
        if (data->particlePos[i].y < boundMin)
        {
          data->particlePos[i].y = boundMin;
          data->particleVel[i].y *= invert;
        }
      }

      data->particleVel[i].x *= decay;
      data->particleVel[i].y *= decay;

      data->particleVel[i].y += 0.02f;


      Fix16 _x = data->particlePos[i].x + (data->particleVel[i].x * vel);
      Fix16 _y = data->particlePos[i].y + (data->particleVel[i].y * vel);

      draw::WuLine(output.frame, data->particlePos[i].x, data->particlePos[i].y, _x, _y, ((i & 1) ? Lime : Green) );

      data->TTL[i] --;
      if (data->TTL[i] <= 0)
        data->alive[i] = false;
    }
  }

  return true;
}