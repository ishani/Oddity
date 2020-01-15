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
 | $Archive: /Ninja/Controls/ninjaLabel.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_LABEL_
#define	__NINJA_LABEL_

// the control class name
// used when actually building dialogs
#define	NINJALABEL_CLASSNAME	("ninjaLabel")


// various draw defines
#define NINJA_LABEL_LEFT_MARGIN		(4u)


// maximum number of characters to store for
// a label's text printing
#define	MAX_NLABEL_TEXT		(255)


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaLabel : public cNinjaControlBase
{
public:

	// control variables
	sChar8	labelText[MAX_NLABEL_TEXT];
	sInt8	labelTextLen;



	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the label
	void draw(HDC hdc);


	// static funtions callable via the control namespace
	static void registerThis(HINSTANCE hInstance);
	static void unregisterThis(HINSTANCE hInstance);
};

// common creation and destruction functions for this control
cNinjaLabel *createNinjaLabel(HWND hwHost, sChar8 *text);
void destroyNinjaLabel(HWND hwHost);
cNinjaLabel *getNinjaLabel(HWND hwHost);

// custom control functions

#endif
