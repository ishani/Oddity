/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Control library entry point
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/NinjaDLL.cpp $
 |
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"

HINSTANCE	ninjaInstance;

/*===========================================================================*\
 | return an active NinjaGDI structure
\*===========================================================================*/

sNinjaGDI	*curNGDI; // filled in at InitNC time
sNinjaGDI	*getActiveNGDI() { return curNGDI; }


/*===========================================================================*\
 | register the Ninja toolset items
\*===========================================================================*/

void InitNinjaControls(HINSTANCE hInstance, sNinjaGDI *inngdi) 
{
  ninjaInstance = hInstance;
  
	// if specified, store the NinjaGDI data
	if(inngdi) curNGDI = inngdi;
	else
	{
		// ..else assign defaults
		curNGDI = new sNinjaGDI();

		// sort out some colours
		curNGDI->ncsBackground		= GetSysColor(COLOR_BTNFACE);
		curNGDI->ncsLight			= GetSysColor(COLOR_BTNHILIGHT);
		curNGDI->ncsDark			= GetSysColor(COLOR_BTNSHADOW);
		curNGDI->ncsNormalText		= GetSysColor(COLOR_BTNTEXT);
		curNGDI->ncsLabel			= GetSysColor(COLOR_APPWORKSPACE);
		curNGDI->ncsLabelText		= GetSysColor(COLOR_CAPTIONTEXT);
		curNGDI->ncsHighlight		= GetSysColor(COLOR_ACTIVECAPTION);

		// setup font structure
		LOGFONT lf;
		memset(&lf,0,sizeof(LOGFONT));

		lf.lfHeight = 14;
		lf.lfWeight = FW_NORMAL;
		lf.lfCharSet = DEFAULT_CHARSET;

		strcpy(lf.lfFaceName,"Arial");
		curNGDI->fontSmall = CreateFontIndirect(&lf);

		lf.lfWeight = FW_EXTRABOLD;
		curNGDI->fontSmallBold = CreateFontIndirect(&lf);

		lf.lfHeight = 24;
		lf.lfWeight = FW_NORMAL;
		curNGDI->fontLarge = CreateFontIndirect(&lf);

		lf.lfWeight = FW_EXTRABOLD;
		curNGDI->fontLargeBold = CreateFontIndirect(&lf);
	}

	// walk through the controls and register them
	// to the passed app instance handle
	cNinjaLabel::registerThis(hInstance);
	cNinjaCheckbox::registerThis(hInstance);
	cNinjaGraph::registerThis(hInstance);
	cNinjaFrame::registerThis(hInstance);
	cNinjaImageView::registerThis(hInstance);
	cNinjaProgressBar::registerThis(hInstance);
  cNinjaButton::registerThis(hInstance);
	cNinjaLED::registerThis(hInstance);
}