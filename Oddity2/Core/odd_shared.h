/*
  .oooooo.         .o8        .o8   o8o      .               
 d8P'  `Y8b       "888       "888   `"'    .o8               
888      888  .oooo888   .oooo888  oooo  .o888oo oooo    ooo 
888      888 d88' `888  d88' `888  `888    888    `88.  .8'  
888      888 888   888  888   888   888    888     `88..8'   
`88b    d88' 888   888  888   888   888    888 .    `888'    
 `Y8bood8P'  `Y8bod88P" `Y8bod88P" o888o   "888"     .8'  2.0
                                                 .o..P'      
                                                 `Y8P'       
                                                             
*/

#pragma once

#include "common.h"
#include "fix16_math.h"

#ifdef _MSC_VER
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------------------------------------------
static const u32 DisplayW    = 16;
static const u32 DisplayH    = 16;
static const u32 DisplaySize = DisplayW * DisplayH;

static const u32 StateSize   = 1024;

typedef struct FrameData {
    u16 pixels[DisplaySize];
} FrameData;

typedef struct StateData {
    u8 memory[StateSize];
} StateData;

struct FrameInput {
    // 1 or -1 denotes a change in dial position
    int  dialChange[3];
    bool dialClick;
};

#ifdef __cplusplus
}
#endif