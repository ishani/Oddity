/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/

#pragma once

#include "oddity.h"
#include "fxp3d.h"

// ---------------------------------------------------------------------------------------------------------------------
#define oMIN(a,b)	(((a)<(b))?(a):(b))	
#define oMAX(a,b)	(((a)>(b))?(a):(b))	

#define DIAL_ADJUST(_dialIndex, _variable, _multiplier, _minV, _maxV) \
  if(input.dialChange[_dialIndex] != 0) \
  { \
    _variable += (input.dialChange[_dialIndex] * _multiplier); \
    if (_variable > _maxV) \
      _variable = _maxV; \
    if (_variable < _minV) \
      _variable = _minV; \
  }


// ---------------------------------------------------------------------------------------------------------------------
inline Fix16 ipart(const Fix16 &v)
{
  int16_t t = v.asInt();
  return Fix16(t);
}

// ---------------------------------------------------------------------------------------------------------------------
inline Fix16 fpart(const Fix16 &v)
{
  Fix16 r(v);
  r -= ipart(v);
  //r.value = (r.value & 0x0000FFFF);
  return r;
}

// ---------------------------------------------------------------------------------------------------------------------
inline Fix16 round(const Fix16 &v)
{
  return ipart(v + 0.5f);
}

// ---------------------------------------------------------------------------------------------------------------------
inline Fix16 rfpart(const Fix16 &v)
{
  return Fix16(1.0f) - fpart(v);
}


// ---------------------------------------------------------------------------------------------------------------------
Fix16 DistanceBetween(Fix16 x, Fix16 y, Fix16 cX, Fix16 cY);
Fix16 DistanceBetweenSq(Fix16 x, Fix16 y, Fix16 cX, Fix16 cY);

void ColourGradient(Fix16 t, bool redFirst, bool halfGradient, byte& r, byte& g);
void ColourBand(Fix16 t, byte& r, byte& g);

void FullSpectrum(const Fix16& t, byte& r, byte& g);
void BlackEdgeSpectrum(const Fix16& t, byte& r, byte& g);
void GBRSpectrum(const Fix16& t, byte& r, byte& g);
void FullGreenSpectrum(const Fix16& t, byte& r, byte& g);


// ---------------------------------------------------------------------------------------------------------------------
Fix16 Perlin3(Fix16 x, Fix16 y, Fix16 z);
Fix16 Perlin2(Fix16 x, Fix16 y);

// ---------------------------------------------------------------------------------------------------------------------
// helpers to decode the R/G intensities out of a single pixel byte
inline void DecodeByte(pixel LEDpixel, byte &r, byte &g)
{
  r = LEDpixel & 0x0f;
  g = (LEDpixel >> 4) & 0x0f;
}

inline void DecodeByteAdditive(pixel LEDpixel, byte &r, byte &g)
{
  r += LEDpixel & 0x0f;
  g += (LEDpixel >> 4) & 0x0f;
}

// ---------------------------------------------------------------------------------------------------------------------
template <typename _T>
inline void ZeroFrame(_T* frame)
{
  for(int i = 0; i < Constants::FrameSize; ++i)
    frame[i] = 0;
}

template <typename _T>
inline void ZeroFrame(_T* frame, _T& zval)
{
  for(int i = 0; i < Constants::FrameSize; ++i)
    frame[i] = zval;
}

template <typename _Tf, typename _Tt>
inline void CopyFrame(_Tf* from, _Tt* to)
{
  for(int i = 0; i < Constants::FrameSize; ++i)
    to[i] = from[i];
}

// ---------------------------------------------------------------------------------------------------------------------
// the long-form way to set a single LED value, with overflow protection and so on
void setLED(pixel* frame, int x, int y, byte r, byte g, bool additive = false, bool swapXY = false);


// ---------------------------------------------------------------------------------------------------------------------
// a simple 0.0 < t < 1.0 colour generator
enum ColourChoice
{
  Red,
  Green,
  Lime,
  Orange,
  Yellow,
  Black,
  DarkRed
};

inline void GetBasicColourIdx(int16_t index, ColourChoice cc, byte& r, byte& g)
{
  if (index > 15)
    index = 15;
  if (index < 0)
    index = 0;

  switch (cc)
  {
  case Red:
    {
      const byte pure_red[16]   = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 }; 
      const byte pure_green[16] = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }; 

      r = pure_red[index];
      g = pure_green[index];
    }
    break;
  case Green:
    {
      const byte pure_red[16]   = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }; 
      const byte pure_green[16] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 }; 

      r = pure_red[index];
      g = pure_green[index];
    }
    break;
  case Lime:
    {
      const byte pure_red[16]   = {  0,  0,  1,  2,  2,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 }; 
      const byte pure_green[16] = {  0,  1,  2,  3,  4,  5,  5,  6,  8,  9, 10, 11, 11, 12, 13, 14 }; 

      r = pure_red[index];
      g = pure_green[index];
    }
    break;
  case Orange:
    {
      const byte pure_red[16]   = {  0,  1,  2,  3,  4,  5,  5,  6,  8,  9, 10, 11, 11, 12, 13, 14 }; 
      const byte pure_green[16] = {  0,  0,  1,  2,  2,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 };  

      r = pure_red[index];
      g = pure_green[index];
    }
    break;
  case Yellow:
    {
      const byte pure_red[16]   = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 }; 
      const byte pure_green[16] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 }; 

      r = pure_red[index];
      g = pure_green[index];
    }
    break;

  case DarkRed:
    {
      r = 1;
      g = 0;
    }
    break;
  case Black:
    {
      r = 0;
      g = 0;
    }
    break;
  }
}

inline void GetBasicColour(Fix16 t, ColourChoice cc, byte& r, byte& g)
{
  int16_t index = (t * fix16_from_float(16.0f)).asInt();
  GetBasicColourIdx(index, cc, r, g);
}

// ---------------------------------------------------------------------------------------------------------------------
// rendering tools
namespace draw
{
  
  // antialiased line
  void WuLine(pixel* frame, Fix16 x1, Fix16 y1, Fix16 x2, Fix16 y2, ColourChoice cc);

#ifdef FONT1616
  void FontGlyph16x16(pixel* frame, char c, int16_t fx, int16_t fy, ColourChoice cc);
#endif // FONT1616

  void FontGlyph8x8(pixel* frame, char c, int16_t fx, int16_t fy, ColourChoice cc);

} // namespace draw

// ---------------------------------------------------------------------------------------------------------------------
class TextScroller
{
public:
  TextScroller();
  
  void Init(const char* text);

  bool Render(pixel* frame, ColourChoice cc, Fix16 &waveinc, Fix16 &wavesize);

protected:
  const char* m_text;

  Fix16   m_wave;
  int32_t m_len,
          m_scroll, 
          m_char, 
          m_nextPixelCountdown;
};