/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | A multi-purpose clickable button
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/ninjaCheckbox.cpp $
 |
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"
#include "GDITools.h"



/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaButton::registerThis(HINSTANCE hInstance)
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
	winClass.lpszClassName	= NINJABUTTON_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tButton Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaButton::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJABUTTON_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaButton::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaButton::draw(HDC hdc)
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	// draw button rect
	if(isOver||!hideEdges)
	{
		if(heavy) njDeepShadedRect(hdc,&hostDim,pressed,curNGDI->ncsBackground);
		else njShadedRect(hdc,&hostDim,pressed,curNGDI->ncsBackground);
	}
	else
	{
		njColourRect(hdc,&hostDim,curNGDI->ncsBackground);
	}


	HFONT newFont = (largeText)?
						(boldText?curNGDI->fontLargeBold:curNGDI->fontLarge):
						(boldText?curNGDI->fontSmallBold:curNGDI->fontSmall);

	HFONT prevFont = (HFONT)SelectObject(hdc,newFont);

	// get text dimensions
	SIZE cbSize;
	GetTextExtentPoint32(hdc,frameText,frameTextLen,&cbSize);
	sUInt32 textTop = ((hostDim.bottom-hostDim.top)>>1)-(cbSize.cy>>1);
	sUInt32 textLat;
	
	// sort out lateral text placement
	switch(alignment)
	{
		case NJALIGN_LEFT:
			textLat = (hostDim.left + NINJA_BUTTON_TEXT_MARGIN);
			break;

		case NJALIGN_CENTER:
			textLat = ((hostDim.right-hostDim.left)>>1)-(cbSize.cx>>1);
			break;
		
		case NJALIGN_RIGHT:
			textLat = ((hostDim.right - NINJA_BUTTON_TEXT_MARGIN)-cbSize.cx);
			break;
	}

	// draw the text
	SetTextColor(hdc,curNGDI->ncsNormalText);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc,textLat,textTop,frameText,frameTextLen);
	SelectObject(hdc,prevFont);
}


/*===========================================================================*\
 | left button is down
\*===========================================================================*/

void cNinjaButton::pressedLB(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	pressed = TRUE;
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | mouse left host window's client area
\*===========================================================================*/

void cNinjaButton::mouseLeave()
{
	pressed = FALSE;
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | mouse has moved over us
\*===========================================================================*/

void cNinjaButton::mouseMove(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	// mouse has re-entered client area
	if(keys&MK_LBUTTON&&pressed==FALSE)
	{
		pressed = TRUE;
		InvalidateRect(hwHost,&hostDim,FALSE);
	}
}


/*===========================================================================*\
 | user clicked with left button
\*===========================================================================*/

void cNinjaButton::clickedLB(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	pressed = FALSE;
	InvalidateRect(hwHost,&hostDim,FALSE);

	// fire off 'we're pushed' message
	sUInt32 hwID = GetWindowLong(hwHost,GWL_ID);
	SendMessage(GetParent(hwHost),WM_NINJA_BUTTON,(WPARAM)this,(LPARAM)hwID);
}


/*===========================================================================*\
 | we are sensitive to state changes, so redraw
\*===========================================================================*/

void cNinjaButton::requestRedraw()
{
	InvalidateRect(hwHost,&hostDim,FALSE);
}



/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaButton *createNinjaButton(HWND hwHost, sChar8 *text, sNJAlign align, sBool hideEdges, sBool large, sBool bold)
{
	// create new manager
	cNinjaButton *cNCB = new cNinjaButton();
	cNCB->resetBase();

	// initialise variables
	cNCB->hwHost = hwHost;
	if(text) strncpy(cNCB->frameText,text,MAX_NLABEL_TEXT);
	else GetWindowText(hwHost,cNCB->frameText,MAX_NLABEL_TEXT);

	// cache string length
	cNCB->frameTextLen = strlen(cNCB->frameText);

	// store text params
	cNCB->boldText	= bold;
	cNCB->largeText	= large;
	cNCB->alignment	= align;
	cNCB->hideEdges = hideEdges;

	// bind to the window
	SetWindowLong(hwHost,GWL_USERDATA,(LONG)cNCB);

	// init the control's window proc
	SendMessage(hwHost,WM_NINJA_INIT,0,0);

	return cNCB;
}


/*===========================================================================*\
 | tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaButton(HWND hwHost)
{
	// get manager and whack it
	cNinjaButton *cNCB = (cNinjaButton*)GetWindowLong(hwHost,GWL_USERDATA);
	delete cNCB;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaButton *getNinjaButton(HWND hwHost)
{
	cNinjaButton *cNCB = (cNinjaButton*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNCB;
}
