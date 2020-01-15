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
 | $Archive: /Ninja/Controls/ninjaLabel.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_BUTTON_
#define	__NINJA_BUTTON_

// the control class name
// used when actually building dialogs
#define	NINJABUTTON_CLASSNAME	("ninjaButton")


// various draw defines
#define NINJA_BUTTON_TEXT_MARGIN		(4u)


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaButton : public cNinjaControlBase
{
public:

  cNinjaButton() : pressed(false) {}

	// control variables
	sChar8	frameText[MAX_NLABEL_TEXT];
	sInt8	frameTextLen;

	// test rendering params
	sBool	hideEdges, pressed;
	sBool	largeText, boldText;
	sNJAlign	alignment;

	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the label
	void draw(HDC hdc);

	// mouse interaction
	void pressedLB(sUInt32 keys, sUInt32 x, sUInt32 y);
	void clickedLB(sUInt32 keys, sUInt32 x, sUInt32 y);
	void mouseMove(sUInt32 keys, sUInt32 x, sUInt32 y);
	void mouseLeave();

	void requestRedraw();

	// static funtions callable via the control namespace
	static void registerThis(HINSTANCE hInstance);
	static void unregisterThis(HINSTANCE hInstance);
};

// common creation and destruction functions for this control
cNinjaButton *createNinjaButton(HWND hwHost, sChar8 *text, sNJAlign align, sBool hideEdges = FALSE, sBool large = FALSE, sBool bold = FALSE);
void destroyNinjaButton(HWND hwHost);
cNinjaButton *getNinjaButton(HWND hwHost);

// custom control functions

#endif
