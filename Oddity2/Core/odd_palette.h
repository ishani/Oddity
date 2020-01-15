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

enum Gradient {
    Gradient_LakePrimaryGreen,
    Gradient_LakePrimaryRed,
    Gradient_Bands,
    Gradient_FullRG,
    Gradient_Hills,
    Gradient_Bands2,
    Gradient_Pulse,

    Gradient_Count
};

// pass in a t value of 0..1 (although code will wrap it) and a choice
// of colour scheme to get back a R,G pair to encode into the output
void
ColourGradient(
    const Gradient gr,
    const fix16_t  t,
    u8&            r,
    u8&            g );
