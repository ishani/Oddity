/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/


#include "oddity.h"
#include "vfx.h"

#include <string.h>

// ---------------------------------------------------------------------------------------------------------------------
TextScroller::TextScroller()
{
  m_len = 0;
}

// ---------------------------------------------------------------------------------------------------------------------
void TextScroller::Init(const char* text)
{
  m_wave = 0.0f;
  m_text = text;
  m_len = strlen(text);
  m_scroll = m_char = m_nextPixelCountdown = 0;
}

// ---------------------------------------------------------------------------------------------------------------------
bool TextScroller::Render(pixel* frame, ColourChoice cc, Fix16 &waveinc, Fix16 &wavesize)
{
  int nextChar1 = (m_char + 1) % m_len;
  int nextChar2 = (m_char + 2) % m_len;
  int nextChar3 = (m_char + 3) % m_len;

  char c1 = m_text[m_char];
  char c2 = m_text[nextChar1];
  char c3 = m_text[nextChar2];
  char c4 = m_text[nextChar3];

  Fix16 f1 = (int16_t)m_char;
  Fix16 f2 = (int16_t)nextChar1;
  Fix16 f3 = (int16_t)nextChar2;
  Fix16 f4 = (int16_t)nextChar3;


  f1 = Fix16(4.0f) + Fix16::sin(m_wave + f1) * wavesize;
  f2 = Fix16(4.0f) + Fix16::sin(m_wave + f2) * wavesize;
  f3 = Fix16(4.0f) + Fix16::sin(m_wave + f3) * wavesize;
  f4 = Fix16(4.0f) + Fix16::sin(m_wave + f4) * wavesize;


//  draw::FontGlyph16x16(frame, c1, (int16_t)(-m_scroll), f3.asInt(), Red);
//  draw::FontGlyph16x16(frame, c2, (int16_t)(-m_scroll) + 16, f4.asInt(), Red);

  draw::FontGlyph8x8(frame, c1, (int16_t)(-m_scroll) + 0, f1.asInt(), cc);
  draw::FontGlyph8x8(frame, c2, (int16_t)(-m_scroll) + 8, f2.asInt(), cc);
  draw::FontGlyph8x8(frame, c3, (int16_t)(-m_scroll) + 16, f3.asInt(), cc);
  draw::FontGlyph8x8(frame, c4, (int16_t)(-m_scroll) + 24, f4.asInt(), cc);

  
  m_wave += waveinc;

  m_nextPixelCountdown --;
  if (m_nextPixelCountdown <= 0)
  {
    m_scroll ++;
    m_nextPixelCountdown = 3;

    if (m_scroll == 8)
    {
      m_scroll = 0;

      m_char ++;
      if (m_char >= m_len)
      {
        m_char = 0;
        return false;
      }
    }
  }

  return true;
}