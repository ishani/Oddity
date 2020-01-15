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
#include "fx_field.h"

// ---------------------------------------------------------------------------------------------------------------------
// given a field choice and a [x,y] which can be 0..1 to cover a portion of the field
// but that can be outside that range as the code will automatically wrap the result to 32x32;
// scale represents what [x,y] maps to
//
fix16_t
field_bilinear_sample(
    const Field   fld,
    const fix16_t x,
    const fix16_t y,
    const fix16_t scale )
{
    const uint16_t* _data = get_field_data( fld );

    // rescale
    const fix16_t _x = fix16_mul( x, scale );
    const fix16_t _y = fix16_mul( y, scale );

    // abs
    const fix16_t _coord_x = fix16_abs_nb( _x );
    const fix16_t _coord_y = fix16_abs_nb( _y );

    // conver to integer cell, wrap at 32
    const int _floorX = ( fix16_floor_to_int( _coord_x ) ) & 31;
    const int _ceilX  = ( fix16_ceil_to_int( _coord_x ) ) & 31;
    const int _floorY = ( fix16_floor_to_int( _coord_y ) ) & 31;
    const int _ceilY  = ( fix16_ceil_to_int( _coord_y ) ) & 31;

    // compute relative weights for the ceil/floor values on each axis
    const fix16_t CX_weight = fix16_fract( _coord_x );
    const fix16_t FX_weight = fix16_sub( fix16_one, CX_weight );
    const fix16_t CY_weight = fix16_fract( _coord_y );
    const fix16_t FY_weight = fix16_sub( fix16_one, CY_weight );

    // bilinear blend
    const fix16_t sample_FX_FY = fix16_mul( fix16_mul( (fix16_t)_data[( _floorX * 32 ) + ( _floorY )], FY_weight ), FX_weight );
    const fix16_t sample_CX_FY = fix16_mul( fix16_mul( (fix16_t)_data[( _ceilX * 32 ) + ( _floorY )], FY_weight ), CX_weight );
    const fix16_t sample_FX_CY = fix16_mul( fix16_mul( (fix16_t)_data[( _floorX * 32 ) + ( _ceilY )], CY_weight ), FX_weight );
    const fix16_t sample_CX_CY = fix16_mul( fix16_mul( (fix16_t)_data[( _ceilX * 32 ) + ( _ceilY )], CY_weight ), CX_weight );

    return fix16_add(
        fix16_add( sample_FX_FY, sample_CX_FY ),
        fix16_add( sample_FX_CY, sample_CX_CY ) );
}