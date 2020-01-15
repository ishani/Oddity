/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Base class for ninja controls
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/ninjaBase.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_BASE_
#define	__NINJA_BASE_


/*===========================================================================*\
 | base class for ninja controls
 | that encapsulates all common callback functions
\*===========================================================================*/

class cNinjaControlBase
{
public:

	// the window handle for 
	// this control
	HWND	hwHost;
	RECT	hostDim;

	// are we tracking the window?
	sBool	tracking;

	// some generic vars
	sBool	heavy;
	sBool	isOver;

	// reset the base class data
	void	resetBase()
	{
		hwHost = NULL;
		tracking = FALSE;
		heavy = FALSE;
		isOver = FALSE;
	}

	// set heavy style, or not (black rim)
	void setHeavyStyle(sBool on) { heavy = on; }


	// mark that the parent window or hierarchy
	// has just changed size
	virtual void sizeChanged()=0;

	// draw the control
	virtual void draw(HDC hdc)=0;

	// mouse interaction
	virtual void pressedLB(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void pressedRB(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void pressedMB(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void clickedLB(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void clickedRB(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void clickedMB(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void mouseMove(sUInt32 keys, sUInt32 x, sUInt32 y){};
	virtual void mouseLeave(){};

	virtual void requestRedraw(){};
};


// main message handler for ninja controls
LRESULT CALLBACK ninjaControlProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// universal heavy style set
void setBaseHeavyStyle(HWND hwCtrl, sBool on);


#endif
