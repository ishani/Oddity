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
 | $Archive: /Ninja/Controls/GDITools.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_GDITOOLS_
#define	__NINJA_GDITOOLS_


/*===========================================================================*\
 | bevelling definitions
\*===========================================================================*/

enum
{
	BV_TOP_LEFT		= (1<<0),
	BV_TOP_RIGHT	= (1<<1),
	BV_BOTTOM_LEFT	= (1<<2),
	BV_BOTTOM_RIGHT = (1<<3)
};


/*===========================================================================*\
 | functions to render primitives to a device context
\*===========================================================================*/

void njColourRect( HDC hdc, RECT *rect, COLORREF face );
void njShadedRect( HDC hdc, RECT *rect, sBool in, COLORREF face );
void njShadedVertLine( HDC hdc, sInt32 x, sInt32 y0, sInt32 y1, BOOL in );
void njShadedHorizLine( HDC hdc, sInt32 y, sInt32 x0, sInt32 x1, BOOL in );
void njDeepShadedRect( HDC hdc, RECT *rect, sBool in, COLORREF face );
void njBevelShadedRect( HDC hdc, RECT *rect, sBool in, sUInt8 bevel, sChar8 bflags, COLORREF face );
void njRect3D( HDC hdc, RECT* rect, sBool in );


/*===========================================================================*\
 | window tracker wrappers
\*===========================================================================*/

void beginWindowTracking(HWND hWnd);
void stopWindowTracking(HWND hWnd);


#endif