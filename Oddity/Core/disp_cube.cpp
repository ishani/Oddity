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

static const Fxp3D verts[8] = {
  Fxp3D(-1.0f,  1.0f, -1.0f),
  Fxp3D( 1.0f,  1.0f, -1.0f),
  Fxp3D( 1.0f, -1.0f, -1.0f),
  Fxp3D(-1.0f, -1.0f, -1.0f),

  Fxp3D(-1.0f,  1.0f,  1.0f),
  Fxp3D( 1.0f,  1.0f,  1.0f),
  Fxp3D( 1.0f, -1.0f,  1.0f),
  Fxp3D(-1.0f, -1.0f,  1.0f),
};

static const int faces[6 * 4] = {
  0,1,2,3,
  1,5,6,2,
  5,4,7,6,
  4,0,3,7,
  0,4,5,1,
  3,2,6,7
};

struct EffectDataCube
{
  Fix16 rotX, rotY, rotZ, distPulse;
  Fix16 fov, spin;
  ColourChoice ccCycle;
};

#ifdef _MSC_VER
static_assert(sizeof(EffectDataCube) < Constants::MemoryPool, "EffectDataCube too big for global memory pool");
#endif // _MSC_VER

// ---------------------------------------------------------------------------------------------------------------------
void cube_init(FXState& state)
{
  EffectDataCube* data = (EffectDataCube*)state.store;

  data->rotX = fix16_mul(fix16_from_int(state.rng.genUInt32(0, 200)), fix16_from_float(0.1f));
  data->rotY = fix16_mul(fix16_from_int(state.rng.genUInt32(0, 200)), fix16_from_float(0.1f));
  data->rotZ = fix16_mul(fix16_from_int(state.rng.genUInt32(0, 200)), fix16_from_float(0.1f));
  data->distPulse = 0.0f;

  data->fov = 10.0f;
  data->spin = 1.0f;

  data->ccCycle = (ColourChoice)state.rng.genUInt32(0, Yellow);
}


// ---------------------------------------------------------------------------------------------------------------------
bool cube_tick(const FrameInput& input, FrameOutput& output, FXState& state)
{
  EffectDataCube* data = (EffectDataCube*)state.store;

  output.fade(3);

  
  DIAL_ADJUST(1, data->fov, 0.15f, 5.0f, 30.0f);
  DIAL_ADJUST(2, data->spin, 0.1f, 0.0f, 1.4f);



  Fxp3D pj[8];

  Fix16 fov(data->fov), dist;

  dist = dist.cos(data->distPulse);
  dist *= 0.5f;
  dist += 2.4f;

  for (int i=0; i<8; i++)
  {
    pj[i] = verts[i].eulerProject(data->rotX, data->rotY, data->rotZ, fov, dist);
  }

  data->rotX += Fix16(0.6f) * data->spin;
  data->rotY += Fix16(1.7f) * data->spin;
  data->rotZ += Fix16(0.3f) * data->spin;
  data->distPulse += Fix16(0.04f) * data->spin;

  for (int f=0; f<6; f++)
  {
    int bi = (f * 4);
    draw::WuLine(output.frame,
      pj[ faces[bi + 0] ].x,
      pj[ faces[bi + 0] ].y,
      pj[ faces[bi + 1] ].x,
      pj[ faces[bi + 1] ].y,
      data->ccCycle);

    draw::WuLine(output.frame,
      pj[ faces[bi + 1] ].x,
      pj[ faces[bi + 1] ].y,
      pj[ faces[bi + 2] ].x,
      pj[ faces[bi + 2] ].y,
      data->ccCycle);

    draw::WuLine(output.frame,
      pj[ faces[bi + 2] ].x,
      pj[ faces[bi + 2] ].y,
      pj[ faces[bi + 3] ].x,
      pj[ faces[bi + 3] ].y,
      data->ccCycle);

    draw::WuLine(output.frame,
      pj[ faces[bi + 3] ].x,
      pj[ faces[bi + 3] ].y,
      pj[ faces[bi + 0] ].x,
      pj[ faces[bi + 0] ].y,
      data->ccCycle);
  }
  return true;
}