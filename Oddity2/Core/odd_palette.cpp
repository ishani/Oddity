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

#include "odd_palette.h"


static const u8 pal_lakeA_1[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  1,  6, 15, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 
static const u8 pal_lakeA_2[32] = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 15, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 

static const u8 pal_ribsA_1[32] = { 0, 0, 0,  2,  1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 9, 14, 15, 11, 7, 2, 1, 0, 0, 0, 0, 0 }; 
static const u8 pal_ribsA_2[32] = { 1, 3, 8, 14, 15, 12, 7, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 14,  8, 2, 0, 0, 0, 0, 0, 0, 0, 1 }; 

static const u8 pal_fullR[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 6, 8, 10, 11, 13, 15, 15, 15, 15, 15, 15, 15, 15, 14, 12, 10, 8, 6, 4, 2, 1 }; 
static const u8 pal_fullG[32] = { 1, 2, 4, 6, 8, 10, 12, 14, 15, 15, 14, 15, 15, 15, 15, 15, 14, 12, 10, 8, 6, 5, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0 }; 

static const u8 pal_2hillA[32] = { 0, 0, 1, 2, 4, 8, 11, 15, 15, 11, 8, 4, 2, 1, 0, 0, 0, 1, 2, 4, 8, 11, 15, 15, 11, 8, 4, 2, 1, 0, 0 }; 
static const u8 pal_2hillB[32] = { 4, 8, 11, 15, 15, 11, 8, 4, 2, 1, 0, 0, 0, 1, 2, 4, 8, 11, 15, 15, 11, 8, 4, 2, 1, 0, 0, 0, 0, 1, 2, }; 

static const u8 pal_bandA[32] = { 1, 3, 14, 10, 2, 0, 1, 3, 14, 10, 2, 0, 1, 3, 14, 10, 2, 0, 1, 3, 14, 10, 2, 0, 1, 3, 14, 10, 2, 0, 0 }; 
static const u8 pal_bandB[32] = { 0, 0,  3,  0, 0, 0, 0, 0,  3,  0, 0, 0, 0, 0,  3,  0, 0, 0, 0, 0,  3,  0, 0, 0, 0, 0,  3,  0, 0, 0, 0 }; 

static const u8 pal_pulse[32] = { 1, 3, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 

static const u8 pal_zero[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 


struct Palette {
    Palette( const u8* r, const u8* g ) : red( r ), green( g ) { }

    const u8* red;
    const u8* green;
};

static const Palette sys_pal[Gradient_Count] = {
    { pal_lakeA_1 , pal_lakeA_2 },
    { pal_lakeA_2 , pal_lakeA_1 },
    { pal_ribsA_1 , pal_ribsA_2 },
    { pal_fullR   , pal_fullG   },
    { pal_2hillA  , pal_2hillB  },
    { pal_bandA   , pal_bandB   },
    { pal_pulse   , pal_zero    },
};

void
ColourGradient(
    const Gradient gr,
    const fix16_t  t,
    u8&            r,
    u8&            g )
{
    int index = fix16_to_int( fix16_mul( t, fix16_from_float( 31.0f ) ) );
    index &= 31;

    r = sys_pal[gr].red[index];
    g = sys_pal[gr].green[index];
}
