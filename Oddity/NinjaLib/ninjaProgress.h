/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Progress Bar
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/ninjaLabel.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_PROGRESSBAR_
#define	__NINJA_PROGRESSBAR_

// the control class name
// used when actually building dialogs
#define	NINJAPROGRESSBAR_CLASSNAME	("ninjaProgressBar")


// distance from each side that the bar starts from
#define	NINJA_PROGRESSBAR_LATERAL_MARGIN		(4)
#define NINJA_PROGRESSBAR_VERTICAL_MARGIN		(4)


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaProgressBar : public cNinjaControlBase
{
public:

	// control variables
	sInt32 minVal, maxVal, curVal;


	// cache values
	sFloat latSize;


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
cNinjaProgressBar *createNinjaProgressBar(HWND hwHost, sInt32 min, sInt32 max, sInt32 val = 0);
void destroyNinjaProgressBar(HWND hwHost);
cNinjaProgressBar *getNinjaProgressBar(HWND hwHost);

// custom control functions

#endif
