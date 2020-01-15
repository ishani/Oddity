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
#include "fix16_math.h"
#include "pcf.h"

// ---------------------------------------------------------------------------------------------------------------------
// we have a set of useful 2D fields precalculated that make
// adding texture and form to effects cheap and effectively
enum Field {
    Field_Axis,         // 
    Field_Bubble4,      //
    Field_Radial,       // distance-from-center
    Field_Turn,         // nice two-pole polar sweep
    Field_Webbing,      // 
    Field_Noise,        // 
    Field_Rays_1,       // rays from center
    Field_Rays_2,       //  .. second variant

    Field_Count
};

// ---------------------------------------------------------------------------------------------------------------------
// return the field data ptr given an enum
inline const uint16_t*
get_field_data(
    const Field fld )
{
    switch( fld ) {
        case Field_Axis:    return pcf_axis;
        case Field_Bubble4: return pcf_bubble4;
        case Field_Radial:  return pcf_radial;
        case Field_Turn:    return pcf_turn;
        case Field_Webbing: return pcf_webbing;
        case Field_Noise:   return pcf_noise;
        case Field_Rays_1:  return pcf_rays_1;
        case Field_Rays_2:  return pcf_rays_2;

        default:
            break;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------------------------------
inline void
fix16_rotate_2d(
    fix16_t&      x,
    fix16_t&      y,
    const fix16_t center_x,
    const fix16_t center_y,
    const fix16_t sin_angle,
    const fix16_t cos_angle )
{
    const fix16_t _prerot_x = fix16_sub( x, center_x );
    const fix16_t _prerot_y = fix16_sub( y, center_y );
    const fix16_t _rotx     = fix16_sub( fix16_mul( _prerot_x, cos_angle ), fix16_mul( _prerot_y, sin_angle ) );
    const fix16_t _roty     = fix16_add( fix16_mul( _prerot_y, cos_angle ), fix16_mul( _prerot_x, sin_angle ) );
    x                       = fix16_add( _rotx, center_x );
    y                       = fix16_add( _roty, center_y );
}

// ---------------------------------------------------------------------------------------------------------------------
// perform a 4-way blended sample across a data field, see impl for more details
fix16_t
field_bilinear_sample(
    const Field   fld,
    const fix16_t x,
    const fix16_t y,
    const fix16_t scale );
