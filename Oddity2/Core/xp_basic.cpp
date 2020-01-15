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
#include "odd_palette.h"

#include "fx_field.h"
#include "fx_noise_perlin.h"

// ---------------------------------------------------------------------------------------------------------------------
struct BasicState {

    inline void
    Reset()
    {
        
    }
};

// ---------------------------------------------------------------------------------------------------------------------
namespace xp {
namespace basic {

// ---------------------------------------------------------------------------------------------------------------------
void
init(
    StateData* state )
{
    BasicState* ws = (BasicState*) state;
    ws->Reset();
}

// ---------------------------------------------------------------------------------------------------------------------
void
tick(
    const FrameInput& input,
    StateData*        state,
    FrameData&        output )
{
    BasicState* ws = (BasicState*) state;

}

}
}    // namespace xp, basic