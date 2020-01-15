/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Checkbox, 2 state
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

void cNinjaCheckbox::registerThis(HINSTANCE hInstance)
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
	winClass.lpszClassName	= NINJACHECKBOX_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tCheckbox Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaCheckbox::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJACHECKBOX_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaCheckbox::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaCheckbox::draw(HDC hdc)
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

	// sort out draw font
	HFONT prevFont = (HFONT)SelectObject(hdc,curNGDI->fontSmall);
	SetTextColor(hdc,curNGDI->ncsNormalText);
	SetBkMode(hdc, TRANSPARENT); 

	// get text dimensions
	SIZE cbSize;
	GetTextExtentPoint32(hdc,cboxLabel,cboxLabelLen,&cbSize);
	sUInt32 textTop = ((hostDim.bottom-hostDim.top)>>1)-(cbSize.cy>>1);

	// draw the checkbox tag
	RECT checkTag;
	checkTag.top = NINJA_CHECKBOX_SPACE_MARGIN;
	checkTag.left = hostDim.left + NINJA_CHECKBOX_SPACE_MARGIN;
	checkTag.right = checkTag.left + NINJA_CHECKBOX_TAG_WIDTH;
	checkTag.bottom = (hostDim.bottom-hostDim.top)-NINJA_CHECKBOX_SPACE_MARGIN;
	njShadedRect(hdc,&checkTag,TRUE,checked?curNGDI->ncsHighlight:curNGDI->ncsBackground);

	// draw the label
	TextOut(hdc,NINJA_CHECKBOX_TAG_WIDTH+(NINJA_CHECKBOX_SPACE_MARGIN*3),textTop,cboxLabel,cboxLabelLen);
	SelectObject(hdc,prevFont);
}


/*===========================================================================*\
 | left button is down
\*===========================================================================*/

void cNinjaCheckbox::pressedLB(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	pressed = TRUE;
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | mouse left host window's client area
\*===========================================================================*/

void cNinjaCheckbox::mouseLeave()
{
	pressed = FALSE;
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | mouse has moved over us
\*===========================================================================*/

void cNinjaCheckbox::mouseMove(sUInt32 keys, sUInt32 x, sUInt32 y)
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

void cNinjaCheckbox::clickedLB(sUInt32 keys, sUInt32 x, sUInt32 y)
{
	pressed = FALSE;
	checked = !checked;
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | we are sensitive to state changes, so redraw
\*===========================================================================*/

void cNinjaCheckbox::requestRedraw()
{
	InvalidateRect(hwHost,&hostDim,FALSE);
}



/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaCheckbox *createNinjaCheckbox(HWND hwHost, sChar8 *text, sBool checked, sBool hideEdges)
{
	// create new manager
	cNinjaCheckbox *cNCB = new cNinjaCheckbox();
	cNCB->resetBase();

	// initialise variables
	cNCB->hwHost = hwHost;
	if(text) strncpy(cNCB->cboxLabel,text,MAX_NLABEL_TEXT);
	else GetWindowText(hwHost,cNCB->cboxLabel,MAX_NLABEL_TEXT);

	// cache string length
	cNCB->cboxLabelLen = strlen(cNCB->cboxLabel);

	// set value defaults
	cNCB->checked = checked;
	cNCB->pressed = FALSE;
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

void destroyNinjaCheckbox(HWND hwHost)
{
	// get manager and whack it
	cNinjaCheckbox *cNCB = (cNinjaCheckbox*)GetWindowLong(hwHost,GWL_USERDATA);
	delete cNCB;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaCheckbox *getNinjaCheckbox(HWND hwHost)
{
	cNinjaCheckbox *cNCB = (cNinjaCheckbox*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNCB;
}
