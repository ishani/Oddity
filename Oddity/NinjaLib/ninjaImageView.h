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
 | $Archive: /Ninja/Controls/ninjaLabel.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_IMAGEVIEW_
#define	__NINJA_IMAGEVIEW_

// the control class name
// used when actually building dialogs
#define	NINJAIMAGEVIEW_CLASSNAME	("ninjaImageView")


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaImageView : public cNinjaControlBase
{
public:

	// storage for the image
	HBITMAP		imageMap;
	sBGRColour	*imageData;
	sUInt32		iWidth,iHeight;

	// navigation variables
	sBool		canPan, canZoom;	// can zoom or pan image?
	sFloat		zoomScale;			// 1.0f = normal
	sInt32		xOrigin, yOrigin;	// central point of image draw
	sInt32		prevX, prevY;

	HCURSOR		crHand,crZoom;
	sInt32		curCursor;


	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the label
	void draw(HDC hdc);

	// image setup functions
	sBGRColour* initImageSize(sUInt32 width, sUInt32 height);
	sBGRColour* getImageDataPtr();
	void setCanPan(sBool onoff);
	void setCanZoom(sBool onoff);
	void resetZoom();
	void resetPan();
	void resetOrigins();

	// mouse interaction
	void pressedLB(sUInt32 keys, sUInt32 x, sUInt32 y);
	void clickedLB(sUInt32 keys, sUInt32 x, sUInt32 y);
	void mouseMove(sUInt32 keys, sUInt32 x, sUInt32 y);
	void mouseLeave();

	// static funtions callable via the control namespace
	static void registerThis(HINSTANCE hInstance);
	static void unregisterThis(HINSTANCE hInstance);
};

// common creation and destruction functions for this control
// image viewer is basic to instance, but then needs several setup calls (above in class)
cNinjaImageView *createNinjaImageView(HWND hwHost);
void destroyNinjaImageView(HWND hwHost);
cNinjaImageView *getNinjaImageView(HWND hwHost);

// custom control functions

#endif
