#pragma once

// the control class name
// used when actually building dialogs
#define	NINJALED_CLASSNAME	("ninjaLED")


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaLED : public cNinjaControlBase
{
public:

  cNinjaLED(sUInt32 _EdgeLen);

	// storage for the image
	sUInt32		iWidth,iHeight;

	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the label
	void draw(HDC hdc);

	// static funtions callable via the control namespace
	static void registerThis(HINSTANCE hInstance);
	static void unregisterThis(HINSTANCE hInstance);
  void decodeFramebuffer( sUInt16 *framebuffer );

protected:

  sUInt32   EdgeLen;
  COLORREF  *m_LEDs;
};

// common creation and destruction functions for this control
// image viewer is basic to instance, but then needs several setup calls (above in class)
cNinjaLED *createNinjaLED(HWND hwHost, sUInt32 _EdgeLen);
void destroyNinjaLED(HWND hwHost);
cNinjaLED *getNinjaLED(HWND hwHost);
