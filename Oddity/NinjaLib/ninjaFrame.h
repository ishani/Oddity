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
 | $Archive: /Ninja/Controls/ninjaFrame.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_FRAME_
#define	__NINJA_FRAME_

// the control class name
// used when actually building dialogs
#define	NINJAFRAME_CLASSNAME	("ninjaFrame")


// various draw defines
#define NINJA_FRAME_TEXT_MARGIN		(4u)


// maximum number of characters to store for
// a frame's text printing
#define	MAX_NLABEL_TEXT		(255)


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaFrame : public cNinjaControlBase
{
public:

	// control variables
	sChar8	frameText[MAX_NLABEL_TEXT];
	sInt8	frameTextLen;

	// test rendering params
	sBool	isIndented;
	sBool	largeText, boldText;
	sNJAlign	alignment;

	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the label
	void draw(HDC hdc);

	void requestRedraw();

	// update this frame's text
	DLL_LINKAGE	void printf(const sChar8 *format, ...);
	DLL_LINKAGE	void setText(const sChar8 *text);

	// static funtions callable via the control namespace
	static void registerThis(HINSTANCE hInstance);
	static void unregisterThis(HINSTANCE hInstance);
};

// common creation and destruction functions for this control
cNinjaFrame *createNinjaFrame(HWND hwHost, sChar8 *text, sNJAlign align, sBool indent = TRUE, sBool large = FALSE, sBool bold = FALSE);
void destroyNinjaFrame(HWND hwHost);
cNinjaFrame *getNinjaFrame(HWND hwHost);

// custom control functions

#endif
