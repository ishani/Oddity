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


namespace draw
{

// ---------------------------------------------------------------------------------------------------------------------
void WuLine(pixel* frame, Fix16 x1, Fix16 y1, Fix16 x2, Fix16 y2, ColourChoice cc)
{
  byte r = 0;
  byte g = 0;

  Fix16 dx = x2 - x1;
  Fix16 dy = y2 - y1;

  bool swapXY = false;
  if (Fix16::abs(dx) < Fix16::abs(dy))
  {
    XORByteSwap(x1.value, y1.value);
    XORByteSwap(x2.value, y2.value);
    XORByteSwap(dx.value, dy.value);
    swapXY = true;
  }

  if (x2 < x1)
  {
    XORByteSwap(x1.value, x2.value);
    XORByteSwap(y1.value, y2.value);
  }

  Fix16 gradient = dy / dx;

  Fix16 xend = round(x1);
  Fix16 yend = y1 + gradient * (xend - x1);
  Fix16 xgap = rfpart(x1 + 0.5f);
  int16_t xpxl1 = xend.asInt();  // this will be used in the main loop
  int16_t ypxl1 = ipart(yend).asInt();

  GetBasicColour(rfpart(yend) * xgap, cc, r, g);
  setLED(frame, xpxl1, ypxl1, r, g, true, swapXY);

  GetBasicColour(fpart(yend) * xgap, cc, r, g);
  setLED(frame, xpxl1, ypxl1 + 1, r, g, true, swapXY);


  Fix16 intery = yend + gradient; // first y-intersection for the main loop


  // handle second endpoint
  xend = round(x2);
  yend = y2 + gradient * (xend - x2);
  xgap = fpart(x2 + 0.5f);
  int16_t xpxl2 = xend.asInt();  // this will be used in the main loop
  int16_t ypxl2 = ipart(yend).asInt();

  GetBasicColour(rfpart(yend) * xgap, cc, r, g);
  setLED(frame, xpxl2, ypxl2, r, g, true, swapXY);

  GetBasicColour(fpart(yend) * xgap, cc, r, g);
  setLED(frame, xpxl2, ypxl2 + 1, r, g, true, swapXY);

  int16_t xa = xpxl1 + 1;
  int16_t xb = xpxl2 - 1;
  
  if (xb - xa > 120)
    return;

  for (; xa <= xb; xa ++)
  {
    GetBasicColour(rfpart(intery), cc, r, g);
    setLED(frame, xa, ipart(intery).asInt(), r, g, true, swapXY);

    GetBasicColour(fpart(intery), cc, r, g);
    setLED(frame, xa, ipart(intery).asInt() + 1, r, g, true, swapXY);

    intery = intery + gradient;
  }
}



} // namespace draw

