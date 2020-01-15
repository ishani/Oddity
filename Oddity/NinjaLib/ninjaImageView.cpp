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



/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaImageView::registerThis(HINSTANCE hInstance)
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
	winClass.lpszClassName	= NINJAIMAGEVIEW_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tImage View Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaImageView::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJAIMAGEVIEW_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaImageView::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaImageView::draw(HDC hdc)
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	sUInt32 wHost = (hostDim.right-hostDim.left);
	sUInt32 hHost = (hostDim.bottom-hostDim.top);

	// create double buffer storage
	HDC hdcN	= CreateCompatibleDC(hdc);
	HDC hdcIMap = CreateCompatibleDC(hdc);
	HBITMAP img = CreateCompatibleBitmap(hdc,wHost,hHost);
	SelectObject(hdcN,img);
	SelectObject(hdcIMap,imageMap);

	// blank the double buffer
	njColourRect(hdcN,&hostDim,curNGDI->ncsBackground);

	// burn image into double buffer
	SetStretchBltMode(hdcN,HALFTONE);
	StretchBlt(hdcN,
		xOrigin - ((sInt32)((sFloat)(iWidth>>1) * zoomScale)),
		yOrigin - ((sInt32)((sFloat)(iHeight>>1) * zoomScale)),
		(sInt32)((sFloat)iWidth * zoomScale),
		(sInt32)((sFloat)iHeight * zoomScale),
		hdcIMap,
		0,
		0,
		iWidth,
		iHeight,
		SRCCOPY);

	// draw frame
	if(heavy) njRect3D(hdcN,&hostDim,TRUE);
	else njRect3D(hdcN,&hostDim,TRUE);


	// copy the buffer, and delete the DC
	BitBlt(hdc,0,0,wHost,hHost,hdcN,0,0,SRCCOPY);
	DeleteObject(img);
	DeleteDC(hdcN);
	DeleteDC(hdcIMap);
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

sBGRColour* cNinjaImageView::initImageSize(sUInt32 width, sUInt32 height)
{
	// clean up old data if present
	if(this->imageMap)
	{
		DeleteObject(this->imageMap);
		this->imageData = NULL;
	}

	// store size
	this->iWidth = width;
	this->iHeight = height;

	// aquire host context
	HDC hostDC = GetDC(this->hwHost);

	// setup bitmap creation params
	BITMAPINFO bmi;
	memset(&bmi.bmiHeader,0,sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth		= this->iWidth;
	bmi.bmiHeader.biHeight		= this->iHeight;
	bmi.bmiHeader.biPlanes		= 1;
	bmi.bmiHeader.biBitCount	= 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	// create the DIB
	imageMap = CreateDIBSection(
		hostDC,
		&bmi,
		DIB_RGB_COLORS,
		(void**)&this->imageData,
		NULL,
		NULL);
	
	// release host context
	ReleaseDC(hwHost,hostDC);

	// reset interaction vars
	resetZoom();
	resetPan();

	return this->imageData;
}

sBGRColour* cNinjaImageView::getImageDataPtr()
{
	return this->imageData;
}



/*===========================================================================*\
 | turn on/off the pan or zoom abilities
\*===========================================================================*/

void cNinjaImageView::setCanPan(sBool onoff)
{
	this->canPan = onoff;
}

void cNinjaImageView::setCanZoom(sBool onoff)
{
	this->canZoom = onoff;
}


/*===========================================================================*\
 | reset functions
\*===========================================================================*/

void cNinjaImageView::resetZoom()
{
	zoomScale = 1.0f;
}

void cNinjaImageView::resetPan()
{
	xOrigin = ((hostDim.right - hostDim.left)>>1);
	yOrigin = ((hostDim.bottom - hostDim.top)>>1);
	prevX = prevY = 0;
}


/*===========================================================================*\
 | left button is down
\*===========================================================================*/

void cNinjaImageView::pressedLB(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	prevY = y;
	prevX = x;
	SetCapture(hwHost);
}


/*===========================================================================*\
 | left button is released
\*===========================================================================*/

void cNinjaImageView::clickedLB(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	ReleaseCapture();
	CURSOR_ARROW;
}


/*===========================================================================*\
 | mouse left host window's client area
\*===========================================================================*/

void cNinjaImageView::mouseLeave()
{
}


/*===========================================================================*\
 | mouse has moved over us
\*===========================================================================*/

void cNinjaImageView::mouseMove(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	if(keys&MK_CONTROL)
	{
		if(keys&MK_LBUTTON)
		{
			// zoom
			sInt32 deltY = (y - prevY);
			zoomScale += ((sFloat)deltY * 0.005f);
			prevY = y;

			// don't invert scale
			CLAMP_LOW(zoomScale,0.1f);

			// redraw
			InvalidateRect(hwHost,&hostDim,FALSE);

			// fire off zoom message
			sUInt32 hwID = GetWindowLong(hwHost,GWL_ID);
			SendMessage(GetParent(hwHost),WM_NINJA_IMGVIEW_ZOOM,(WPARAM)this,(LPARAM)hwID);
		}
		SetCursor(this->crZoom);
	}
	else
	{
		if(keys&MK_LBUTTON)
		{
			// move center
			xOrigin += (x - prevX);
			yOrigin += (y - prevY);
			prevY = y;
			prevX = x;

			// redraw
			InvalidateRect(hwHost,&hostDim,FALSE);

			// fire off zoom message
			sUInt32 hwID = GetWindowLong(hwHost,GWL_ID);
			SendMessage(GetParent(hwHost),WM_NINJA_IMGVIEW_PAN,(WPARAM)this,(LPARAM)hwID);
		}
		SetCursor(this->crHand);
	}
}



/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaImageView *createNinjaImageView(HWND hwHost)
{
	// create new manager
	cNinjaImageView *cNIV = new cNinjaImageView();
	cNIV->resetBase();

	// initialise variables
	cNIV->hwHost = hwHost;
	cNIV->imageData = NULL;
	cNIV->canPan = cNIV->canZoom = FALSE;
	cNIV->iWidth = cNIV->iHeight = 0;
	cNIV->zoomScale = 1.0f;

	cNIV->crHand = LoadCursor(ninjaInstance, MAKEINTRESOURCE(IDI_NINJA_HAND));
	cNIV->crZoom = LoadCursor(ninjaInstance, MAKEINTRESOURCE(IDI_NINJA_ZOOM));

	// bind to the window
	SetWindowLong(hwHost,GWL_USERDATA,(LONG)cNIV);

	// init the control's window proc
	SendMessage(hwHost,WM_NINJA_INIT,0,0);

	return cNIV;
}


/*===========================================================================*\
 | tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaImageView(HWND hwHost)
{
	// get manager and whack it
	cNinjaImageView *cNIV = (cNinjaImageView*)GetWindowLong(hwHost,GWL_USERDATA);
	delete cNIV;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaImageView *getNinjaImageView(HWND hwHost)
{
	cNinjaImageView *cNIV = (cNinjaImageView*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNIV;
}
