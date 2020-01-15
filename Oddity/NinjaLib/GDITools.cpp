/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Some Windows GDI utility functions
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/GDITools.cpp $
 |
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"
#include "GDITools.h"


/*===========================================================================*\
 | draw a solid block of colour
\*===========================================================================*/

void njColourRect( HDC hdc, RECT *rect, COLORREF face )
{
	HPEN	pNull	= CreatePen(PS_SOLID,1,face);
	HBRUSH	bFace	= CreateSolidBrush(face);

	DeleteObject(SelectObject(hdc,bFace));
	DeleteObject(SelectObject(hdc,pNull));
	Rectangle(hdc,rect->left,rect->top,rect->right,rect->bottom);
	DeleteObject(bFace);
	DeleteObject(pNull);
}


/*===========================================================================*\
 | draw a shaded rect , button stylee
\*===========================================================================*/

void njShadedRect( HDC hdc, RECT *rect, sBool in, COLORREF face )
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	
	HPEN	pLight	= CreatePen(PS_SOLID,1,curNGDI->ncsLight); 
	HPEN	pDark	= CreatePen(PS_SOLID,1,curNGDI->ncsDark);
	HBRUSH	bFace	= CreateSolidBrush(face);

	DeleteObject(SelectObject(hdc,bFace));
	DeleteObject(SelectObject(hdc,in?pDark:pLight));

	// draw main rect area with light pen
	Rectangle(hdc,rect->left,rect->top,rect->right,rect->bottom);

	DeleteObject(SelectObject(hdc,in?pLight:pDark));

	// lower edges
	MoveToEx(hdc,rect->left,rect->bottom-1,NULL);
	LineTo(hdc,rect->right-1,rect->bottom-1);
	LineTo(hdc,rect->right-1,rect->top);

	DeleteObject(bFace);
	DeleteObject(pLight);
	DeleteObject(pDark);
}


/*===========================================================================*\
 | a shaded vertical line
\*===========================================================================*/

void njShadedVertLine( HDC hdc, sInt32 x, sInt32 y0, sInt32 y1, BOOL in )
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	
	HPEN hLight = CreatePen( PS_SOLID, 0, curNGDI->ncsLight );
	HPEN hDark  = CreatePen( PS_SOLID, 0, curNGDI->ncsDark );
	
	DeleteObject(SelectObject( hdc, in ? hDark : hLight));
	MoveToEx( hdc, x, y0, NULL );
	LineTo( hdc, x, y1 );
	SelectObject( hdc, in ? hLight : hDark );
	MoveToEx( hdc, x+1, y0, NULL );
	LineTo( hdc, x+1, y1 );
	DeleteObject( hLight );
	DeleteObject( hDark );	
}


/*===========================================================================*\
 | prince of denmark?
\*===========================================================================*/

void njShadedHorizLine( HDC hdc, sInt32 y, sInt32 x0, sInt32 x1, BOOL in )
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	
	HPEN hLight = CreatePen( PS_SOLID, 0, curNGDI->ncsLight );
	HPEN hDark  = CreatePen( PS_SOLID, 0, curNGDI->ncsDark );
	
	DeleteObject(SelectObject( hdc, in?hDark:hLight ));
	MoveToEx( hdc, x0, y, NULL );
	LineTo( hdc, x1, y );
	SelectObject( hdc, in?hLight:hDark );
	MoveToEx( hdc, x0, y+1, NULL );
	LineTo( hdc, x1, y+1 );
	
	DeleteObject( hLight );
	DeleteObject( hDark );
}


/*===========================================================================*\
 | draw a shaded rect, with a darker outline
\*===========================================================================*/

void njDeepShadedRect( HDC hdc, RECT *rect, sBool in, COLORREF face )
{
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	HPEN	pLight	= CreatePen(PS_SOLID,1,curNGDI->ncsLight); 
	HPEN	pDark	= CreatePen(PS_SOLID,1,curNGDI->ncsDark);
	HPEN	pVDark	= CreatePen(PS_SOLID,1,RGB(0,0,0));
	HBRUSH	bFace	= CreateSolidBrush(face);

	DeleteObject(SelectObject(hdc,bFace));
	DeleteObject(SelectObject(hdc,pVDark));

	// draw main rect area with light pen
	Rectangle(hdc,rect->left,rect->top,rect->right,rect->bottom);

	// upper edges
	DeleteObject(SelectObject(hdc,in?pDark:pLight));

	MoveToEx(hdc,rect->left+1,rect->bottom-2,NULL);
	LineTo(hdc,rect->left+1,rect->top+1);
	LineTo(hdc,rect->right-2,rect->top+1);

	DeleteObject(SelectObject(hdc,in?pLight:pDark));

	// lower edges
	MoveToEx(hdc,rect->left+1,rect->bottom-2,NULL);
	LineTo(hdc,rect->right-2,rect->bottom-2);
	LineTo(hdc,rect->right-2,rect->top+1);

	DeleteObject(bFace);
	DeleteObject(pLight);
	DeleteObject(pDark);
	DeleteObject(pVDark);
}


/*===========================================================================*\
 | draw a shaded rect with a controllable bevel
\*===========================================================================*/

void njBevelShadedRect( HDC hdc, RECT *rect, sBool in, sUInt8 bevel, sChar8 bflags, COLORREF face )
{
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	RECT inner; 
	inner.left		= rect->left+bevel;
	inner.right		= rect->right-bevel;
	inner.top		= rect->top+bevel;
	inner.bottom	= rect->bottom-bevel;

	HPEN	pLight	= CreatePen(PS_SOLID,1,curNGDI->ncsLight); 
	HPEN	pDark	= CreatePen(PS_SOLID,1,curNGDI->ncsDark);
	HPEN	pVDark	= CreatePen(PS_SOLID,1,RGB(0,0,0));
	HBRUSH	bFace	= CreateSolidBrush(face);

	DeleteObject(SelectObject(hdc,bFace));
	DeleteObject(SelectObject(hdc,pVDark));

	MoveToEx(hdc,inner.left,rect->bottom,NULL);
	LineTo(hdc,rect->left,inner.bottom);
	LineTo(hdc,rect->left,inner.top);
	LineTo(hdc,inner.left,rect->top);
	LineTo(hdc,inner.right,rect->top);
	LineTo(hdc,rect->right,inner.top);
	LineTo(hdc,rect->right,inner.bottom);
	LineTo(hdc,inner.right,rect->bottom);
	LineTo(hdc,inner.left,rect->bottom);

	DeleteObject(bFace);
	DeleteObject(pLight);
	DeleteObject(pDark);
	DeleteObject(pVDark);
}


/*===========================================================================*\
 | draw shaded outline
\*===========================================================================*/

void njRect3D( HDC hdc, RECT* rect, sBool in )
{
	HPEN hLight = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNHIGHLIGHT ) );
	HPEN hDark = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNSHADOW ) );
	
	SelectObject( hdc, in ? hDark : hLight );
	MoveToEx( hdc, rect->left, rect->bottom-1, NULL );
	LineTo( hdc, rect->left, rect->top );
	LineTo( hdc, rect->right-1, rect->top );
	SelectObject( hdc, in ? hLight : hDark );
	LineTo( hdc, rect->right-1, rect->bottom-1 );
	LineTo( hdc, rect->left, rect->bottom-1 );
	SelectObject( hdc, GetStockObject(BLACK_PEN) );
	DeleteObject( hLight );
	DeleteObject( hDark );
}


/*===========================================================================*\
 | window tracker wrappers
\*===========================================================================*/

void beginWindowTracking(HWND hWnd)
{
	TRACKMOUSEEVENT	tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.hwndTrack = hWnd;
	tme.dwFlags = TME_LEAVE;	// just watch leaving

	_TrackMouseEvent(&tme);
}

void stopWindowTracking(HWND hWnd)
{
	TRACKMOUSEEVENT	tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.hwndTrack = hWnd;
	tme.dwFlags = TME_CANCEL|TME_LEAVE;

	_TrackMouseEvent(&tme);
}