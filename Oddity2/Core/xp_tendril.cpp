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
struct TendrilState {
    fix16_t time_f;
    fix16_t time_r;
    fix16_t time_g;
    fix16_t time_x;

    fix16_t time_spiral;
    fix16_t time_spiral_dir;

    inline void
    Reset()
    {
        time_f = fix16_zero;
        time_r = c_f16_6;
        time_g = c_f16_6;
        time_x = fix16_zero;

        time_spiral     = fix16_zero;
        time_spiral_dir = fix16_zero;
    }
};

fix16_t
spiral(
    const fix16_t time,
    const fix16_t pra,
    const fix16_t divl,
    const fix16_t x,
    const fix16_t y,
    const fix16_t ofx,
    const fix16_t ofy )
{
    // find distance from the center of the screen
    const fix16_t _dd = fix16_mul(
        fix16_distance_between_sq( x, y, c_f16_15_pt_5, c_f16_15_pt_5 ),
        (fix16_t) 0x00000111 );    // 1 / (15.5 ^ 2)

    // pick an angle for rotation, modify by distance from center to create spiral pattern
    const fix16_t _angle = fix16_add( time, fix16_mul( _dd, pra ) );

    const fix16_t _xx = fix16_sub( x, fix16_add( ofx, c_f16_15_pt_5 ) );
    const fix16_t _yy = fix16_sub( y, fix16_add( ofy, c_f16_15_pt_5 ) );

    const fix16_t _cos = fix16_cos( _angle );
    const fix16_t _sin = fix16_sin( _angle );

    // rotate point by angle
    const fix16_t _x = fix16_sub( fix16_mul( _xx, _cos ), fix16_mul( _yy, _sin ) );
    const fix16_t _y = fix16_add( fix16_mul( _yy, _cos ), fix16_mul( _xx, _sin ) );

    // find a unsigned field value for each axis
    const fix16_t _w = fix16_mul( fix16_abs_nb( _x ), divl );
    const fix16_t _h = fix16_mul( fix16_abs_nb( _y ), divl );

    return fix16_min( _w, _h );
}

// ---------------------------------------------------------------------------------------------------------------------
namespace xp {
namespace tendril {

// ---------------------------------------------------------------------------------------------------------------------
void
init(
    StateData* state )
{
    TendrilState* ws = (TendrilState*) state;
    ws->Reset();
}

// ---------------------------------------------------------------------------------------------------------------------
void
tick(
    const FrameInput& input,
    StateData*        state,
    FrameData&        output )
{
    TendrilState* ws = (TendrilState*) state;

    ws->time_f = fix16_add( ws->time_f, c_f16_pt_01 );
    ws->time_g = fix16_add( ws->time_g, c_f16_pt_02 );
    ws->time_r = fix16_add( ws->time_r, c_f16_pt_03 );
    ws->time_x = fix16_add( ws->time_x, c_f16_pt_0025 );

    const fix16_t time_f = ws->time_f;
    const fix16_t time_g = ws->time_g;
    const fix16_t time_r = ws->time_r;
    const fix16_t time_x = ws->time_x;

    const fix16_t off_lr = fix16_mul( fix16_sin( time_f ), c_f16_pt_707 );
    const fix16_t off_xr = fix16_mul( fix16_cos( time_g ), c_f16_pt_707 );

    // const fix16_t scaler = p3lerp( off_xr, c_f16_10, c_f16_16 );

    const fix16_t pra  = ( fx_noise_perlin2( time_g, time_f ) );
    const fix16_t pra2 = fix16_add( -c_f16_3, fix16_mul( pra, c_f16_6 ) );

    const fix16_t _cos_r = fix16_cos( -pra );
    const fix16_t _sin_r = fix16_sin( -pra );

    const fix16_t dv   = ( fx_noise_perlin2( time_r, time_f ) );
    const fix16_t divl = p3lerp( dv, c_f16_1_over_9, c_f16_1_over_14 );

    const fix16_t _spiral_dir = fx_noise_perlin2( time_x, c_f16_32 );

    fix16_t _spiral_toffset;
    if( _spiral_dir >= c_f16_pt_5 ) {

        // [0.5 .. 1.0] -> [0.0 .. 1.0]
        const fix16_t _dir_tv = fix16_mul( fix16_sub( _spiral_dir, c_f16_pt_5 ), c_f16_2 );

        _spiral_toffset = p3lerp( _dir_tv, c_f16_pt_03, c_f16_pt_06 );
        
    } else {

        // [0.0 .. 0.5] -> [0.0 .. 1.0]
        const fix16_t _dir_tv = fix16_mul( _spiral_dir, c_f16_2 );

        _spiral_toffset = -p3lerp( _dir_tv, c_f16_pt_06, c_f16_pt_03 );
    }

    // exp-approach blend to new value
    ws->time_spiral_dir = fix16_add( ws->time_spiral_dir,
                                     fix16_mul( fix16_sub( _spiral_toffset, ws->time_spiral_dir ), c_f16_pt_25 ) );

    // add current direction to the spiral movement time
    ws->time_spiral            = fix16_add( ws->time_spiral, ws->time_spiral_dir );
    const fix16_t _spiral_time = ws->time_spiral;

    fix16_t surf_u = fix16_zero;
    fix16_t surf_v = fix16_zero;

    for( int16_t x = 0; x < 16; x++ ) {
        for( int16_t y = 0; y < 16; y++ ) {
            surf_v = fix16_add( surf_v, c_f16_1_over_16 );

            const fix16_t off_u = fix16_add( surf_u, off_lr );
            const fix16_t off_v = fix16_add( surf_v, fix16_mul( off_lr, c_f16_1_pt_5 ) );

            // create a pair of noise-driven mutations to the spiral shape.
            // .. too expensive to call noise functions per pixel at this point,
            // so we use a prebuilt noise field to do the job
            //
            const fix16_t _noise_ptrb_1 = field_bilinear_sample(
                Field_Noise,
                fix16_add( time_f, surf_u ),
                fix16_add( time_g, surf_v ),
                c_f16_5 );

            const fix16_t _noise_ptrb_2 = field_bilinear_sample(
                Field_Noise,
                fix16_add( time_g, off_u ),
                fix16_add( time_r, off_v ),
                c_f16_3 );

            const fix16_t _result_spiral = spiral(
                _spiral_time,
                pra2,
                divl,
                fix16_add( fix16_from_int( x + 8 ), off_xr ),
                fix16_add( fix16_from_int( y + 8 ), off_lr ),
                fix16_add( -c_f16_8, fix16_mul( _noise_ptrb_1, c_f16_15 ) ),
                fix16_add( -c_f16_8, fix16_mul( _noise_ptrb_2, c_f16_15 ) ) );

            fix16_t blob_x = off_v;
            fix16_t blob_y = off_u;
            fix16_rotate_2d(
                blob_x,
                blob_y,
                c_f16_pt_05,
                c_f16_pt_05,
                _sin_r,
                _cos_r );

            const fix16_t _result_displace = fix16_mul(
                field_bilinear_sample( Field_Webbing, blob_x, blob_y, c_f16_16 ),
                c_f16_pt_3 );

            // mesh the spiral and the displacement, then clamp it
            const fix16_t _final = fix16_min( fix16_one,
                                              fix16_add( _result_spiral, _result_displace ) );

            // reduce to output colour gradient, write it out
            u8 r, g;
            ColourGradient( Gradient_LakePrimaryRed, _final, r, g );

            output.pixels[( y * 16 ) + x] = r | ( g << 4 );
        }

        surf_v = fix16_zero;
        surf_u = fix16_add( surf_u, c_f16_1_over_16 );
    }
}

}
}    // namespace xp, tendril