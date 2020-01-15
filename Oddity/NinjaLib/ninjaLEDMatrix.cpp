/*===========================================================================*\
|
| Ninja Custom Control Library
|
| Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
|===========================================================================*
|
| Image edit and viewing chamber
|
| $Author: Harry Denholm $ 
| $Revision: 1 $
| $Date: 22/05/01 23:18 $ 
| $Archive: /Ninja/Controls/ninjaLabel.cpp $
|
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"
#include "GDITools.h"

static COLORREF ledColors[5][5];

/*===========================================================================*\
| register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaLED::registerThis(HINSTANCE hInstance)
{
  WNDCLASS winClass;

  winClass.style			= CS_DBLCLKS | CS_OWNDC | 
    CS_HREDRAW | CS_VREDRAW;
  winClass.lpfnWndProc	= ninjaControlProc;
  winClass.cbClsExtra		= 0;
  winClass.cbWndExtra		= 0;
  winClass.hInstance		= hInstance;
  winClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
  winClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
  winClass.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
  winClass.lpszMenuName	= NULL; 
  winClass.lpszClassName	= NINJALED_CLASSNAME;

  // register the window class, or fail and warn the user
  if(!RegisterClass(&winClass))
    MessageBox(NULL,"Ninja Error:\n\nLED View Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
| register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaLED::unregisterThis(HINSTANCE hInstance)
{
  // unbind the control from the app instance
  UnregisterClass(NINJALED_CLASSNAME,hInstance);
}


/*===========================================================================*\
| size of parent or hierarchy has changed - update
| any dimensions based caches
\*===========================================================================*/

void cNinjaLED::sizeChanged()
{
  if(!hwHost) return;
  GetClientRect(hwHost,&hostDim);
}


/*===========================================================================*\
| draw the control onto a device context
\*===========================================================================*/

void cNinjaLED::draw(HDC hdc)
{
  // get current GDI data setup
  sNinjaGDI	*curNGDI = getActiveNGDI();
  if(!curNGDI) return;


  RECT checkTag;
  checkTag.top = 0;
  checkTag.left = 0;
  checkTag.right = checkTag.left + (EdgeLen * (14)) + 3 + 3;
  checkTag.bottom = checkTag.top + (EdgeLen * (14)) + 3 + 3;

  // create double buffer storage
  HDC hdcN	= CreateCompatibleDC(hdc);
  HBITMAP img = CreateCompatibleBitmap(hdc,checkTag.right + 1,checkTag.bottom + 1);
  SelectObject(hdcN,img);

  njColourRect(hdcN, &checkTag, RGB(0,0,0));

  for (sUInt32 y=0; y<EdgeLen; y++)
  {
    for (sUInt32 x=0; x<EdgeLen; x++)
    {
      // draw the checkbox tag
      checkTag.top = 2 + (x * (14));
      checkTag.left = 2 + (y * (14));
      checkTag.right = checkTag.left + EdgeLen;
      checkTag.bottom = checkTag.top + EdgeLen;
      njColourRect(hdcN, &checkTag, m_LEDs[ (y * EdgeLen) + (EdgeLen -1 -x) ]);
    }
  }

  // copy the buffer, and delete the DC
  BitBlt(hdc,0,0,checkTag.right + 1,checkTag.bottom + 1,hdcN,0,0,SRCCOPY);
  DeleteObject(img);
  DeleteDC(hdcN);
}

void cNinjaLED::decodeFramebuffer( sUInt16 *framebuffer )
{
  for (sUInt32 y=0; y<EdgeLen; y++)
  {
    for (sUInt32 x=0; x<EdgeLen; x++)
    {
      sUInt16 pixel = framebuffer[(y * EdgeLen) + x];

      sUInt8 r = pixel & 0x0f;
      sUInt8 g = (pixel >> 4) & 0x0f;
      sUInt8 b = (pixel >> 8) & 0x0f;

      m_LEDs[(y * EdgeLen) + x] = RGB(r << 4, g << 4, b << 4);
    }
  }
}

cNinjaLED::cNinjaLED( sUInt32 _EdgeLen )
{
  m_LEDs = new COLORREF[_EdgeLen * _EdgeLen];
  EdgeLen = _EdgeLen;
}


/*===========================================================================*\
| create a new instance of the control's manager class and
| insert it into the host's userdata entry
\*===========================================================================*/

cNinjaLED *createNinjaLED(HWND hwHost, sUInt32 _EdgeLen)
{
  // create new manager
  cNinjaLED *cLED = new cNinjaLED(_EdgeLen);
  cLED->resetBase();

  cLED->hwHost = hwHost;

  for (int r=0; r<5; r++)
  {
    for (int g=0; g<5; g++)
    {
      int led_red = (r * 55);
      int led_green = (g * 55);

      ledColors[r][g] = RGB(led_red, led_green, 0);
    }
  }

  // bind to the window
  SetWindowLong(hwHost,GWL_USERDATA,(LONG)cLED);

  // init the control's window proc
  SendMessage(hwHost,WM_NINJA_INIT,0,0);

  return cLED;
}


/*===========================================================================*\
| tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaLED(HWND hwHost)
{
  // get manager and whack it
  cNinjaLED *cLED = (cNinjaLED*)GetWindowLong(hwHost,GWL_USERDATA);
  delete cLED;

  // delete userdata
  SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
| get the control manager pointer from a host
\*===========================================================================*/

cNinjaLED *getNinjaLED(HWND hwHost)
{
  cNinjaLED *cLED = (cNinjaLED*)GetWindowLong(hwHost,GWL_USERDATA);
  return cLED;
}
