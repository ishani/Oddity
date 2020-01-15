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

#ifdef OXP_SCROLL

#include "odd_shared.h"
#include "odd_palette.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "font.h"

#include "pcf.h"
#include "fx_field.h"

const int32_t   g_ticksPerScroll    = 3;
const int32_t   g_glyphSize         = 16;
const int32_t   g_glyphOverlap      = 4;
const int32_t   g_glyphOffset       = g_glyphSize - g_glyphOverlap;

// ---------------------------------------------------------------------------------------------------------------------
struct ScrollState
{
  const char* m_text;
  
  fix16_t     m_bounce;
  fix16_t     m_bgoff;
  fix16_t     m_ripple;
  int32_t     m_len,
              m_scroll, 
              m_char, 
              m_nextPixelCountdown;

  inline void Reset()
  {
    m_bounce = 0;
    m_bgoff = 0;
    m_ripple = 0;
    m_text = " TEXT SCROLLER ! ";
    m_len = strlen(m_text);
    m_scroll = m_char = m_nextPixelCountdown = 0;
  }

  inline void Tick()
  {
    m_nextPixelCountdown --;
    if (m_nextPixelCountdown <= 0)
    {
      m_nextPixelCountdown = g_ticksPerScroll;

      m_scroll ++;
      if (m_scroll == g_glyphSize)
      {
        m_scroll = g_glyphOverlap;

        m_char ++;
        if (m_char >= m_len)
        {
          m_char = 0;
          return;
        }
      }
    }
  }
};


// ---------------------------------------------------------------------------------------------------------------------
namespace xp { namespace scroll {

// ---------------------------------------------------------------------------------------------------------------------
void init(
  StateData* state)
{
  ScrollState* ws = (ScrollState*)state;
  ws->Reset();
}

static const fix16_t fix16_pt_0625       = 0x00001000;

void blitFontGlyph(fix16_t* buffer, char c, int16_t fx, int16_t fy, fix16_t cycle)
{
  const u8* fontBuf = getFontGlyphData16x16(c);
  if (!fontBuf)
    return;

  const fix16_t _origin_surf_u = fix16_mul( fix16_from_int(fx), c_f16_1_over_16 );
  const fix16_t _origin_surf_v = fix16_add( cycle, fix16_mul( fix16_from_int(fy), c_f16_1_over_16 ) );

  fix16_t surf_u = _origin_surf_u;
  fix16_t surf_v = _origin_surf_v;
  
  for (int y=0, addr=0; y<16; y++, addr += 16)
  {
    for (int x=0; x<16; x++)
    {
      const u8 set = fontBuf[ addr + x ];

      if (set > 0)
      {
        const int16_t buf_x = (fx + x);
        const int16_t buf_y = (fy + y);

        if ( buf_x >=0 && 
             buf_x < 16 &&
             buf_y >= 0 &&
             buf_y < 16 )
        {
          if ( set == 3 )
          {
            const fix16_t u2 = field_bilinear_sample(
              Field_Noise, 
              surf_u, 
              surf_v, 
              c_f16_5);

            buffer[ (buf_y * 16) + buf_x ] = u2;
          }
          else
          {
            buffer[ (buf_y * 16) + buf_x ] = fix16_neg_one;
          }
        }
      }

      surf_u = fix16_add( surf_u, c_f16_1_over_16 ); 
    }

    surf_u = _origin_surf_u;
    surf_v = fix16_add( surf_v, c_f16_1_over_16 ); 
  }
}


// ---------------------------------------------------------------------------------------------------------------------
void tick(
  const FrameInput& input,
  StateData*        state,
  FrameData&        output)
{
  ScrollState* ws = (ScrollState*)state;

  int nextChar1 = (ws->m_char + 1) % ws->m_len;
  int nextChar2 = (ws->m_char + 2) % ws->m_len;
  
  const char c1 = ws->m_text[ws->m_char];
  const char c2 = ws->m_text[nextChar1];
  const char c3 = ws->m_text[nextChar2];
  
  const int16_t _scroll_pt = (int16_t)(-ws->m_scroll);

  fix16_t f1 = fix16_mul( fix16_from_int(ws->m_char), fix16_half_pi );
  fix16_t f2 = fix16_mul( fix16_from_int(nextChar1), fix16_half_pi );
  fix16_t f3 = fix16_mul( fix16_from_int(nextChar2), fix16_half_pi );
  
  f1 = fix16_mul( fix16_sin( fix16_add( ws->m_bounce, f1) ), c_f16_3 );
  f2 = fix16_mul( fix16_sin( fix16_add( ws->m_bounce, f2) ), c_f16_3 );
  f3 = fix16_mul( fix16_sin( fix16_add( ws->m_bounce, f3) ), c_f16_3 );
  
  fix16_t m_buffer[ DisplaySize ];  
  memset( m_buffer, 0, DisplaySize * sizeof(fix16_t) );
  
  blitFontGlyph(m_buffer, c1, _scroll_pt,                                 fix16_to_int(f1), ws->m_bgoff);
  blitFontGlyph(m_buffer, c2, _scroll_pt + g_glyphOffset,                 fix16_to_int(f2), ws->m_bgoff);
  blitFontGlyph(m_buffer, c3, _scroll_pt + g_glyphOffset + g_glyphOffset, fix16_to_int(f3), ws->m_bgoff);
  
  
  u8 r, g;
  for ( int16_t x=0; x<16; x++)
  {
    for ( int16_t y=0; y<16; y++)
    {
      const size_t addr1 = (y * 16) + x;
      const size_t addr2 = (x * 16) + (15 - y);

      
      if ( m_buffer[addr1] > 0 )
      {
        ColourGradient( Gradient_FullRG, m_buffer[addr1], r, g );
      }
      else if ( m_buffer[addr1] == 0 )
      {
        const size_t addr_pcf = ((8 + y) * 32) + (8 + x);
        const fix16_t ripple = fix16_mul( c_f16_pt_3, fix16_add( ws->m_ripple, pcf_radial[addr_pcf] ) );
        ColourGradient( Gradient_Pulse, ripple, r, g );
      }
      else
      {
        r = g = 0;
      }

      output.pixels[ addr2 ] = r | ( g << 4 );
    }
  }

  ws->m_bounce = fix16_add( ws->m_bounce, c_f16_pt_06 ); 
  ws->m_bgoff = fix16_add( ws->m_bgoff, c_f16_pt_03 );
  ws->m_ripple = fix16_add( ws->m_ripple, c_f16_pt_02 );
  
  ws->Tick();
}

} } // namespace xp, scroll 

#endif // OXP_SCROLL
