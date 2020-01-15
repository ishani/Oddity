/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Progress Bar
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

void cNinjaProgressBar::registerThis(HINSTANCE hInstance)
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
	winClass.lpszClassName	= NINJAPROGRESSBAR_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tProgress Bar Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaProgressBar::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJAPROGRESSBAR_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaProgressBar::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);

	// cache a bar block size
	latSize = ((hostDim.right - hostDim.left) - (NINJA_PROGRESSBAR_LATERAL_MARGIN*2)) / 100.0f;
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaProgressBar::draw(HDC hdc)
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	// draw the shaded rectangle
	if(heavy) njDeepShadedRect(hdc,&hostDim,TRUE,curNGDI->ncsBackground);
	else njShadedRect(hdc,&hostDim,TRUE,curNGDI->ncsBackground);
	
	// size of bar to draw
	sUInt32 barSize = floatToInt(((100.0f / (sFloat)(maxVal - minVal)) * curVal) * latSize);

	// draw it!
	RECT bar;
	bar.left = hostDim.left + NINJA_PROGRESSBAR_LATERAL_MARGIN;
	bar.right = bar.left + barSize;
	bar.top = hostDim.top + NINJA_PROGRESSBAR_VERTICAL_MARGIN;
	bar.bottom = hostDim.bottom - NINJA_PROGRESSBAR_VERTICAL_MARGIN;
	njColourRect(hdc,&bar,curNGDI->ncsHighlight);
}



/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaProgressBar *createNinjaProgressBar(HWND hwHost, sInt32 min, sInt32 max, sInt32 val)
{
	// create new manager
	cNinjaProgressBar *cNL = new cNinjaProgressBar();
	cNL->resetBase();

	// initialise variables
	cNL->hwHost = hwHost;

	cNL->minVal = min;
	cNL->maxVal = max;
	cNL->curVal = val;

	// bind to the window
	SetWindowLong(hwHost,GWL_USERDATA,(LONG)cNL);

	// init the control's window proc
	SendMessage(hwHost,WM_NINJA_INIT,0,0);

	return cNL;
}


/*===========================================================================*\
 | tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaProgressBar(HWND hwHost)
{
	// get manager and whack it
	cNinjaProgressBar *cNL = (cNinjaProgressBar*)GetWindowLong(hwHost,GWL_USERDATA);
	delete cNL;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaProgressBar *getNinjaProgressBar(HWND hwHost)
{
	cNinjaProgressBar *cNL = (cNinjaProgressBar*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNL;
}
