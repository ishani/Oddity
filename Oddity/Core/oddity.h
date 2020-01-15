/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/

#pragma once
#include "oddity_memory.h"

#define ROTATE_SCREEN_CCW 1

namespace vfx
{

// ---------------------------------------------------------------------------------------------------------------------
void init(FXState& state);

// ---------------------------------------------------------------------------------------------------------------------
bool tick(
  const FrameInput& input,
  FXState& state,
  FrameOutput& output);

} // namespace vfx
