/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Label control - flat shaded
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

void cNinjaLabel::registerThis(HINSTANCE hInstance)
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
	winClass.lpszClassName	= NINJALABEL_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tLabel Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaLabel::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJALABEL_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaLabel::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaLabel::draw(HDC hdc)
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	// draw the background colour frame
	if(heavy) njShadedRect(hdc,&hostDim,TRUE,curNGDI->ncsLabel);
	else njColourRect(hdc,&hostDim,curNGDI->ncsLabel );
	

	HFONT prevFont = (HFONT)SelectObject(hdc,curNGDI->fontSmallBold);

	// get text dimensions
	SIZE cbSize;
	GetTextExtentPoint32(hdc,labelText,labelTextLen,&cbSize);
	sUInt32 textTop = ((hostDim.bottom-hostDim.top)>>1)-(cbSize.cy>>1);

	// draw the text
	SetTextColor(hdc,curNGDI->ncsLabelText);
	SetBkMode(hdc, TRANSPARENT); 
	TextOut(hdc,NINJA_LABEL_LEFT_MARGIN,textTop,labelText,labelTextLen);
	SelectObject(hdc,prevFont);
}



/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaLabel *createNinjaLabel(HWND hwHost, sChar8 *text)
{
	// create new manager
	cNinjaLabel *cNL = new cNinjaLabel();
	cNL->resetBase();

	// initialise variables
	cNL->hwHost = hwHost;
	if(text) strncpy(cNL->labelText,text,MAX_NLABEL_TEXT);
	else GetWindowText(hwHost,cNL->labelText,MAX_NLABEL_TEXT);

	// cache string length
	cNL->labelTextLen = strlen(cNL->labelText);

	// bind to the window
	SetWindowLong(hwHost,GWL_USERDATA,(LONG)cNL);

	// init the control's window proc
	SendMessage(hwHost,WM_NINJA_INIT,0,0);

	return cNL;
}


/*===========================================================================*\
 | tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaLabel(HWND hwHost)
{
	// get manager and whack it
	cNinjaLabel *cNL = (cNinjaLabel*)GetWindowLong(hwHost,GWL_USERDATA);
	delete cNL;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaLabel *getNinjaLabel(HWND hwHost)
{
	cNinjaLabel *cNL = (cNinjaLabel*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNL;
}
