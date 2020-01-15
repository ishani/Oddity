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
 | $Archive: /Ninja/Controls/ninjaCheckbox.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_CHECKBOX_
#define	__NINJA_CHECKBOX_

// the control class name
// used when actually building dialogs
#define	NINJACHECKBOX_CLASSNAME	("ninjaCheckbox")


// various draw defines
#define NINJA_CHECKBOX_SPACE_MARGIN	(4u)
#define NINJA_CHECKBOX_TAG_WIDTH	(12u)



// maximum number of characters to store for
// a label's text printing
#define	MAX_CBOX_LABEL_TEXT		(255)


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaCheckbox : public cNinjaControlBase
{
public:

  cNinjaCheckbox() : pressed(false) {}

	// control variables
	sChar8	cboxLabel[MAX_CBOX_LABEL_TEXT];
	sInt8	cboxLabelLen;
	sBool	checked,pressed,hideEdges;


	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the checkbox
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
cNinjaCheckbox *createNinjaCheckbox(HWND hwHost, sChar8 *text, sBool checked, sBool hideEdges);
void destroyNinjaCheckbox(HWND hwHost);
cNinjaCheckbox *getNinjaCheckbox(HWND hwHost);

// custom control functions

#endif
