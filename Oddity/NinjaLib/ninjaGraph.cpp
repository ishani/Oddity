/*===========================================================================*\
 |
 | Ninja Custom Control Library
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Implimentation of a scroll graph, ie. like a processor usage / load graph
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /Ninja/Controls/ninjaGraph.cpp $
 |
\*===========================================================================*/


#include "ninjaFW.h"
#include "ninja.h"
#include "GDITools.h"



/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaGraph::registerThis(HINSTANCE hInstance)
{
	WNDCLASS winClass;

	winClass.style			= CS_DBLCLKS | CS_OWNDC | 
							  CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc	= ninjaControlProc;
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0;
	winClass.hInstance		= hInstance;
	winClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
	winClass.lpszMenuName	= NULL; 
	winClass.lpszClassName	= NINJAGRAPH_CLASSNAME;

	// register the window class, or fail and warn the user
	if(!RegisterClass(&winClass))
		MessageBox(NULL,"Ninja Error:\n\n\tGraph Class Unregistered!","Error",MB_OK);
}


/*===========================================================================*\
 | register the control with windows, bound to the passed app instance handle
\*===========================================================================*/

void cNinjaGraph::unregisterThis(HINSTANCE hInstance)
{
	// unbind the control from the app instance
	UnregisterClass(NINJAGRAPH_CLASSNAME,hInstance);
}


/*===========================================================================*\
 | size of parent or hierarchy has changed - update
 | any dimensions based caches
\*===========================================================================*/

void cNinjaGraph::sizeChanged()
{
	if(!hwHost) return;
	GetClientRect(hwHost,&hostDim);

	// allocate enough values to represent each pixel in the graph
	// minus two for the shaded borders
	numGraphValues = (hostDim.right - hostDim.left) - 2;
	graphValues = (sFloat*)malloc(sizeof(float)*numGraphValues);
	memset(graphValues,0,sizeof(float)*numGraphValues);
}


/*===========================================================================*\
 | draw the control onto a device context
\*===========================================================================*/

void cNinjaGraph::draw(HDC hdc)
{
	// get current GDI data setup
	sNinjaGDI	*curNGDI = getActiveNGDI();
	if(!curNGDI) return;

	// work out the scale value to map graph values into 
	// drawable values
	sFloat graphScale = 1.0f / (maxV-minV);

	// height of graph is 2 off client area height
	// to accomodate the border
	sUInt32 graphHeight = (hostDim.bottom - hostDim.top) - 2;

	// create double buffer storage
	HDC hdcN = CreateCompatibleDC(hdc);
	HBITMAP img = CreateCompatibleBitmap(hdc,numGraphValues+2,graphHeight+2);
	SelectObject(hdcN,img);

	// draw button rect
	njShadedRect(hdcN,&hostDim,TRUE,curNGDI->ncsBackground);

	// create pen to draw graph with
	HPEN	pGraph = CreatePen(PS_SOLID,1,curNGDI->ncsHighlight);
	DeleteObject(SelectObject(hdcN,pGraph));

	// loop and draw the values
	sUInt32 x,y,count=0;
	while(count<numGraphValues)
	{
		// start at current value and work forward
		// until all values have been plotted
		sUInt32 enumPoint = curGraphPt+count;
		if(enumPoint>=numGraphValues) enumPoint -= numGraphValues;

		// work out points to plot
		sUInt32 newX = (count+1);
		sUInt32 newY = graphHeight- (sUInt32)((graphValues[enumPoint] * graphScale) * (sFloat)graphHeight);

		// clamp 'em
		if(newY<0) newY = 0;
		if(newY>graphHeight) newY = graphHeight;

		// if first value, lock the previous coords to current ones
		if(count==0) { x = newX; y = newY; }

		// draw line from previous to current
		if(solidGraph)
		{
			MoveToEx(hdcN,newX,newY,NULL);
			LineTo(hdcN,newX,graphHeight);
		}
		else
		{
			MoveToEx(hdcN,x,y,NULL);
			LineTo(hdcN,newX,newY);
		}
		
		// save current to draw from in next pass
		x = newX; y = newY;
		
		// next value
		count++;
	}

	// trash the pen gdi object
	DeleteObject(pGraph);

	// copy the buffer, and delete the DC
	BitBlt(hdc,0,0,numGraphValues+2,graphHeight+2,hdcN,0,0,SRCCOPY);
	DeleteDC(hdcN);
	DeleteObject(img);
}



/*===========================================================================*\
 | add a value to the graph, possibly overwriting existing
\*===========================================================================*/

void cNinjaGraph::addValue(sFloat newval)
{
	// stuff new value in
	graphValues[curGraphPt] = newval;	
	
	// increment to next value, or loop to 0
	curGraphPt++;
	if(curGraphPt>=numGraphValues) curGraphPt = 0;

	// redraw us
	InvalidateRect(hwHost,&hostDim,FALSE);
}


/*===========================================================================*\
 | create a new instance of the control's manager class and
 | insert it into the host's userdata entry
\*===========================================================================*/

cNinjaGraph *createNinjaGraph(HWND hwHost, sFloat min, sFloat max, sBool solid)
{
	// create new manager
	cNinjaGraph *cNG = new cNinjaGraph();
	cNG->resetBase();

	// initialise variables
	cNG->hwHost = hwHost;

	// set graph range
	cNG->minV = min;
	cNG->maxV = max;
	cNG->curGraphPt = cNG->numGraphValues = 0;

	// assign other vars
	cNG->solidGraph = solid;

	// bind to the window
	SetWindowLong(hwHost,GWL_USERDATA,(LONG)cNG);

	// init the control's window proc
	SendMessage(hwHost,WM_NINJA_INIT,0,0);

	return cNG;
}


/*===========================================================================*\
 | tidy up a control manager class and remove it from a host window
\*===========================================================================*/

void destroyNinjaGraph(HWND hwHost)
{
	// get manager and whack it
	cNinjaGraph *cNG = (cNinjaGraph*)GetWindowLong(hwHost,GWL_USERDATA);
	free(cNG->graphValues);
	delete cNG;

	// delete userdata
	SetWindowLong(hwHost,GWL_USERDATA,NULL);
}


/*===========================================================================*\
 | get the control manager pointer from a host
\*===========================================================================*/

cNinjaGraph *getNinjaGraph(HWND hwHost)
{
	cNinjaGraph *cNG = (cNinjaGraph*)GetWindowLong(hwHost,GWL_USERDATA);
	return cNG;
}
