/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/

#pragma once

// ---------------------------------------------------------------------------------------------------------------------
#include "fixedpoint.h"
#include "RNG.h"

#ifdef _MSC_VER
#include <stddef.h>
#endif 
typedef unsigned char byte;

typedef unsigned short pixel;

// ---------------------------------------------------------------------------------------------------------------------
struct Constants
{
  enum Enum
  {
    // output configuration
    FrameWidth  = 16,
    FrameHeight = 16,
    FrameSize   = FrameWidth * FrameHeight,

    // size of the shared global memory pool
    MemoryPool  = 8 * 1024
  };
};


// ---------------------------------------------------------------------------------------------------------------------
//
struct FrameInput
{
  // 1 or -1 denotes a change in dial position
  int   dialChange[3];
  bool  dialClick;
};

struct FrameOutput
{
  // assumes fixed 16x16 RG configuration, 2-bits per pixel.
  // frame stored 1-byte per pixel (XXRR XXGG)
  pixel  frame[Constants::FrameSize];

  void clear()
  {
    for(uint32_t i = 0; i < Constants::FrameSize; ++i)
      frame[i] = 0;
  }

  void fade(int32_t times)
  {
    byte r, g;
    for(uint32_t i = 0; i < Constants::FrameSize; ++i)
    {
      pixel &pxl = frame[i];  

      for (int32_t q=0; q<times; q++)
      {
        r = pxl & 0x0f;
        g = (pxl >> 4) & 0x0f;

        if (r > 0)
          r --;
        if (g > 0)
          g --;

        pxl = r | (g << 4);
      }
    }
  }

  void fadeRGS(int32_t Rtimes, int32_t Gtimes)
  {
    byte r, g;
    for(uint32_t i = 0; i < Constants::FrameSize; ++i)
    {
      pixel &pxl = frame[i];  

      r = pxl & 0x0f;
      g = (pxl >> 4) & 0x0f;

      for (int32_t q=0; q<Rtimes; q++)
      {
        if (r > 0)
          r --;
      }
      for (int32_t q=0; q<Gtimes; q++)
      {
        if (g > 0)
          g --;
      }

      pxl = r | (g << 4);

    }
  }

};

// ---------------------------------------------------------------------------------------------------------------------
// 
struct FXState
{
  uint32_t      counter;
  RNG           rng;

  byte          store[Constants::MemoryPool];
};