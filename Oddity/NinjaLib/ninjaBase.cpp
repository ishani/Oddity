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
 | $Archive: /Ninja/Controls/ninjaBase.cpp $
 |
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"
#include "GDITools.h"


/*===========================================================================*\
 | the main windows message handler for the ninja custom control
 | this is a message cracker that passes input into the control class
\*===========================================================================*/

LRESULT CALLBACK ninjaControlProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// aquire the class data from the window's GWL_USERDATA entry
	cNinjaControlBase *cd = (cNinjaControlBase*)GetWindowLong(hwnd,GWL_USERDATA);
	if(cd!=NULL)
	{
		switch(msg)
		{
			// manager initialised
			case WM_NINJA_INIT:
			{
				// perform any initialisation
				cd->sizeChanged();
			}
			break;

			// the size has been changed
			case WM_SIZE:
			{
				// update any caches based
				// on control dimensions
				cd->sizeChanged();
			}
			break;

			// left button is down
			case WM_LBUTTONDOWN: 
				{
					cd->pressedLB(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(!cd->tracking) { beginWindowTracking(hwnd); cd->tracking = TRUE; }
				}
				break;

			// middle button is down
			case WM_MBUTTONDOWN: 
				{
					cd->pressedMB(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(!cd->tracking) { beginWindowTracking(hwnd); cd->tracking = TRUE; }
				}
				break;

			// right button is down
			case WM_RBUTTONDOWN: 
				{
					cd->pressedRB(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(!cd->tracking) { beginWindowTracking(hwnd); cd->tracking = TRUE; }
				}
				break;

			case WM_MOUSELEAVE:
				{
					if(cd->isOver)
					{
						cd->isOver = FALSE;
						cd->requestRedraw();
					}
					cd->mouseLeave();
					if(cd->tracking) { stopWindowTracking(hwnd); cd->tracking = FALSE; }
				}
				break;

			// left button released
			case WM_LBUTTONUP: 
				{
					cd->clickedLB(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(cd->tracking) { stopWindowTracking(hwnd); cd->tracking = FALSE; }
				}
				break;

			// middle button released
			case WM_MBUTTONUP: 
				{
					cd->clickedMB(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(cd->tracking) { stopWindowTracking(hwnd); cd->tracking = FALSE; }
				}
				break;

			// right button released
			case WM_RBUTTONUP: 
				{
					cd->clickedRB(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(cd->tracking) { stopWindowTracking(hwnd); cd->tracking = FALSE; }
				}
				break;

			// right button released
			case WM_MOUSEMOVE: 
				{
					if(!cd->isOver)
					{
						cd->isOver = TRUE;
						cd->requestRedraw();
					}
					cd->mouseMove(wparam,GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
					if(!cd->tracking) { beginWindowTracking(hwnd); cd->tracking = TRUE; }
				}
				break;

			// redraw
			case WM_PAINT:
			{
				// begin paint cycle
				PAINTSTRUCT ps;
				HDC hdc;
				hdc = BeginPaint( hwnd, &ps );

				// draw
				cd->draw(hdc);

				// end paint cycle
				EndPaint( hwnd, &ps );
			}
			break;
		}
	}

// process any messages that we didn't take care of 
return (DefWindowProc(hwnd, msg, wparam, lparam));
}


void setBaseHeavyStyle(HWND hwCtrl, sBool on)
{
	cNinjaControlBase *cNCB = (cNinjaControlBase*)GetWindowLong(hwCtrl,GWL_USERDATA);
	cNCB->setHeavyStyle(on);
}
