/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Frame control - a shaded container rectangle
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/ninjaFrame.cpp $
 |
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"
#include "GDITools.h"



/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaFrame::registerThis(HINSTANCE hInstance)
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
	winClass.lpszClassName	= NINJAFRAME_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tFrame Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaFrame::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJAFRAME_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaFrame::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);
}


/*===========================================================================*\
 | we are sensitive to state changes, so redraw
\*===========================================================================*/

void cNinjaFrame::requestRedraw()
{
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | update this frame's text
\*===========================================================================*/

DLL_LINKAGE	void cNinjaFrame::printf(const sChar8 *format, ...)
{
	sChar8 buf[MAX_NLABEL_TEXT];

	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);

	strcpy(this->frameText,buf);
	this->frameTextLen = strlen(this->frameText);
}

DLL_LINKAGE	void cNinjaFrame::setText(const sChar8 *text)
{
	strcpy(this->frameText,text);
	this->frameTextLen = strlen(this->frameText);
}



/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaFrame::draw(HDC hdc)
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	// draw the shaded rectangle
	if(heavy) njDeepShadedRect(hdc,&hostDim,isIndented,curNGDI->ncsBackground);
	else njShadedRect(hdc,&hostDim,isIndented,curNGDI->ncsBackground);


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
			textLat = (hostDim.left + NINJA_FRAME_TEXT_MARGIN);
			break;

		case NJALIGN_CENTER:
			textLat = ((hostDim.right-hostDim.left)>>1)-(cbSize.cx>>1);
			break;
		
		case NJALIGN_RIGHT:
			textLat = ((hostDim.right - NINJA_FRAME_TEXT_MARGIN)-cbSize.cx);
			break;
	}

	// draw the text
	SetTextColor(hdc,curNGDI->ncsNormalText);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc,textLat,textTop,frameText,frameTextLen);
	SelectObject(hdc,prevFont);
}



/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaFrame *createNinjaFrame(HWND hwHost, sChar8 *text, sNJAlign align, sBool indent, sBool large, sBool bold)
{
	// create new manager
	cNinjaFrame *cNF = new cNinjaFrame();
	cNF->resetBase();

	// initialise variables
	cNF->hwHost = hwHost;
	if(text) strncpy(cNF->frameText,text,MAX_NLABEL_TEXT);
	else GetWindowText(hwHost,cNF->frameText,MAX_NLABEL_TEXT);

	// cache string length
	cNF->frameTextLen = strlen(cNF->frameText);

	// store text params
	cNF->isIndented = indent;
	cNF->boldText	= bold;
	cNF->largeText	= large;
	cNF->alignment	= align;

	// bind to the window
	SetWindowLong(hwHost,GWL_USERDATA,(LONG)cNF);

	// init the control's window proc
	SendMessage(hwHost,WM_NINJA_INIT,0,0);

	return cNF;
}


/*===========================================================================*\
 | tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaFrame(HWND hwHost)
{
	// get manager and whack it
	cNinjaFrame *cNF = (cNinjaFrame*)GetWindowLong(hwHost,GWL_USERDATA);
	delete cNF;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaFrame *getNinjaFrame(HWND hwHost)
{
	cNinjaFrame *cNF = (cNinjaFrame*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNF;
}
