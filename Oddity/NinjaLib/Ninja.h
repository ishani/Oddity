/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Public includable file for the ninja library
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/Ninja.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_MAIN_
#define	__NINJA_MAIN_

#include "resource.h"


#define DLL_LINKAGE

extern HINSTANCE	ninjaInstance;


/*===========================================================================*\
 | general enum definitions, etc
\*===========================================================================*/

typedef enum sNJAlign
{
	NJALIGN_LEFT,
	NJALIGN_CENTER,
	NJALIGN_RIGHT,

} sNJAlign;



/*===========================================================================*\
 | ninja control headers
\*===========================================================================*/

#include "ninjaBase.h"
#include "ninjaLabel.h"
#include "ninjaCheckbox.h"
#include "ninjaGraph.h"
#include "ninjaFrame.h"
#include "ninjaImageView.h"
#include "ninjaProgress.h"
#include "ninjaButton.h"
#include "ninjaLEDMatrix.h"


/*===========================================================================*\
 | custom ninja message types passed between windows and hosts
\*===========================================================================*/

#define	WM_NINJA_INIT			(WM_USER+0x0100)

#define	WM_NINJA_BUTTON			(WM_USER+0x0101)		// button pressed
#define	WM_NINJA_IMGVIEW_PAN	(WM_USER+0x0102)		// image view panned
#define	WM_NINJA_IMGVIEW_ZOOM	(WM_USER+0x0103)		// image view zoomed


/*===========================================================================*\
 | definition for a set of colours to be used by Ninja
\*===========================================================================*/

typedef struct sNinjaGDI
{
	COLORREF	ncsBackground;
	COLORREF	ncsLight;
	COLORREF	ncsDark;
	COLORREF	ncsLabel;
	COLORREF	ncsNormalText;
	COLORREF	ncsLabelText;
	COLORREF	ncsHighlight;

	HFONT		fontSmall;
	HFONT		fontSmallBold;
	HFONT		fontLarge;
	HFONT		fontLargeBold;

} sNinjaGDI;

sNinjaGDI	*getActiveNGDI();



/*===========================================================================*\
 | initialize the control set - pass NULL for colours to use windows styles
\*===========================================================================*/

void InitNinjaControls(HINSTANCE hInstance, sNinjaGDI *inngdi);


#endif