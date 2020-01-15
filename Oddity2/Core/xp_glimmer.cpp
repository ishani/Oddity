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
struct GlimmerState {

    fix16_t time_d;
    fix16_t time_e;
    fix16_t time_f;
    fix16_t time_g;

    inline void
    Reset()
    {
        time_d = c_f16_6;
        time_e = c_f16_4;
        time_f = fix16_zero;
        time_g = fix16_one;
    }
};

// ---------------------------------------------------------------------------------------------------------------------
namespace xp {
namespace glimmer {

// ---------------------------------------------------------------------------------------------------------------------
void
init(
    StateData* state )
{
    GlimmerState* ws = (GlimmerState*) state;
    ws->Reset();
}

// ---------------------------------------------------------------------------------------------------------------------
void
tick(
    const FrameInput& input,
    StateData*        state,
    FrameData&        output )
{
    GlimmerState* ws = (GlimmerState*) state;

    fix16_t fx = ws->time_d;
    fix16_t fy = fix16_mul( ws->time_d, c_f16_pt_25 );
    fix16_t fd = c_f16_pt_05;

    ws->time_d = fix16_add( ws->time_d, c_f16_pt_03 );
    ws->time_e = fix16_add( ws->time_e, c_f16_pt_02 );
    ws->time_f = fix16_add( ws->time_f, c_f16_pt_01 );
    ws->time_g = fix16_add( ws->time_g, c_f16_pt_03 );

    const fix16_t _cos1_r = fix16_cos( -ws->time_e );
    const fix16_t _sin1_r = fix16_sin( -ws->time_e );
    const fix16_t _cos2_r = fix16_cos( ws->time_d );
    const fix16_t _sin2_r = fix16_sin( ws->time_d );

    const fix16_t off_lr = fix16_mul( fix16_add( fix16_sin( ws->time_g ), fix16_one ), c_f16_pt_5 );
    const fix16_t off_xr = fix16_mul( fix16_add( fix16_cos( ws->time_e ), fix16_one ), c_f16_pt_5 );
    const fix16_t off_ko = fix16_mul( fix16_add( fix16_cos( ws->time_d ), fix16_one ), c_f16_pt_5 );

    fix16_t off_2 = fix16_cos( ws->time_f );
    fix16_t off_1 = ( fix16_mul( fx_noise_perlin2( off_2, ws->time_f ), c_f16_8 ) );
    off_2         = ( fix16_mul( off_2, c_f16_8 ) );

    const fix16_t recp = p3lerp( off_lr, c_f16_1_over_8, c_f16_1_over_18 );

    fix16_t surf_u = c_f16_pt_75;
    fix16_t surf_v = c_f16_pt_75;

    for( int16_t x = 0; x < 16; x++ ) {
        for( int16_t y = 0; y < 16; y++ ) {

            surf_v = fix16_add( surf_v, c_f16_1_over_16 );

            fix16_t xl_u = surf_u;
            fix16_t xl_v = surf_v;
            fix16_rotate_2d(
                xl_u,
                xl_v,
                fix16_one,
                fix16_one,
                _sin1_r,
                _cos1_r );

            fix16_t qs_u = surf_u;
            fix16_t qs_v = surf_v;
            fix16_rotate_2d(
                qs_u,
                qs_v,
                c_f16_pt_25,
                c_f16_pt_25,
                _sin1_r,
                _cos1_r );

            fix16_t turn_u = surf_u;
            fix16_t turn_v = surf_v;
            fix16_rotate_2d(
                turn_u,
                turn_v,
                c_f16_pt_75,
                c_f16_pt_75,
                _sin2_r,
                _cos2_r );

            fix16_t q1 = field_bilinear_sample( Field_Bubble4, turn_u, qs_v, c_f16_16 );
            fix16_t q2 = field_bilinear_sample( Field_Turn, xl_u, xl_v, c_f16_16 );
            fix16_t q3 = (fix16_t)pcf_radial[( ( y + 8 ) * 32 ) + ( x + 8 )];

            fix16_t nuts = p3lerp( off_lr, q1, q2 );
            fix16_t v1   = p3lerp( off_xr, nuts, q3 );

            fix16_t vA = field_bilinear_sample( Field_Rays_1, turn_u, turn_v, c_f16_11 );
            fix16_t vB = field_bilinear_sample( Field_Rays_2, qs_u, qs_v, c_f16_12 );
            fix16_t v2 = fix16_min( vA, vB );

            fix16_t dis = fix16_distance_between_sq( fix16_from_int( x - 8 ), fix16_from_int( y - 8 ), off_1, off_2 );
            dis         = fix16_mul( dis, (fix16_t) 0x00000400 );
            dis         = fix16_mul( dis, recp );

            v1 = fix16_mul( v1, dis );

            fix16_t v = field_bilinear_sample(
                Field_Noise,
                v1,
                ws->time_d,
                c_f16_4 );

            //v         = fix16_mul( v, v );
            const fix16_t a = field_bilinear_sample(
                Field_Noise,
                ws->time_e,
                v2,
                c_f16_4 );

            v = fix16_mul( v, a );

            v = fix16_mul( v, c_f16_2 );

            fy = fix16_add( fy, fd );

            //  fix16_t qq = lut_df_four[ ( ( y + 8 ) * 32 ) + ( x + 8 ) ];
            //  qq = fix16_add( qq, time_f );

            u8 r, g;
            ColourGradient( Gradient_Bands, v, r, g );

            output.pixels[( y * 16 ) + x] = r | ( g << 4 );
        }

        fy = fix16_mul( ws->time_d, c_f16_pt_25 );
        fx = fix16_add( fx, fd );

        surf_v = c_f16_pt_75;
        surf_u = fix16_add( surf_u, c_f16_1_over_16 );
    }
}

}
}    // namespace xp, glimmer