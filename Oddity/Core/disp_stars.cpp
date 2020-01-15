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

#define STAR_COUNT 45

struct EffectDataStars
{
  Fix16 rotX, rotY, rotZ;
  Fix16 spin;

  Fxp3D   stars[STAR_COUNT];

  void spawn(FXState& state, int16_t index)
  {
    stars[index].x = fix16_cos( fix16_mul(fix16_from_int(state.rng.genUInt32(0, 500)), fix16_from_float(0.04f)));
    stars[index].y = fix16_cos( fix16_mul(fix16_from_int(state.rng.genUInt32(0, 500)), fix16_from_float(0.04f)));
    stars[index].z = fix16_cos( fix16_mul(fix16_from_int(state.rng.genUInt32(0, 500)), fix16_from_float(0.04f)));
  }
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataStars) < Constants::MemoryPool, "EffectDataStars too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void stars_init(FXState& state)
{
  EffectDataStars* data = (EffectDataStars*)state.store;

  data->rotX = fix16_mul(fix16_from_int(state.rng.genUInt32(0, 200)), fix16_from_float(0.1f));
  data->rotY = fix16_mul(fix16_from_int(state.rng.genUInt32(0, 200)), fix16_from_float(0.1f));
  data->rotZ = fix16_mul(fix16_from_int(state.rng.genUInt32(0, 200)), fix16_from_float(0.1f));

  for (uint16_t i=0; i<STAR_COUNT; i++)
  {
    data->spawn(state, i);
  }

  data->spin = 1.5f;
}


// ---------------------------------------------------------------------------------------------------------------------
bool stars_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataStars* data = (EffectDataStars*)state.store;

  output.fadeRGS(4, 1);

  DIAL_ADJUST(2, data->spin, 0.1f, 0.0f, 2.8f);


  Fix16 fov(5.0f), dist(0.25f);
    
  for (int i=0; i<STAR_COUNT; i++)
  {
    Fxp3D pj = data->stars[i].eulerProject(data->rotX, data->rotY, data->rotZ, fov, dist);

    setLED(output.frame, pj.x.asInt(), pj.y.asInt(), 5, 15);
  }

  data->rotZ += Perlin2(data->rotY, data->rotX) * data->spin;
  data->rotY += Fix16(0.95f) * data->spin;
  data->rotX += Fix16(0.3f) * data->spin;

  return true;
}