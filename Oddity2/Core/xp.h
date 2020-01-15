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

#include "common.h"
#include "odd_shared.h"

#define DISP(_act)  \
  _act(tendril)     \
  _act(glimmer)
  
#define PREDEC(_disp)               \
  namespace xp { namespace _disp {    \
  extern void init(StateData* state); \
  extern void tick(const FrameInput& input, StateData* state, FrameData& output); \
  } } 

DISP(PREDEC)

