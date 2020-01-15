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
 | $Archive: /Ninja/Controls/ninjaGraph.h $
 |
\*===========================================================================*/


#ifndef	__NINJA_GRAPH_
#define	__NINJA_GRAPH_

// the control class name
// used when actually building dialogs
#define	NINJAGRAPH_CLASSNAME	("ninjaGraph")


/*===========================================================================*\
 | class that controls the custom control
 | a pointer to a local instance of one of these is stored in the host
 | window's userdata
\*===========================================================================*/

class cNinjaGraph : public cNinjaControlBase
{
public:

	// control variables
	sFloat	maxV,minV;
	sFloat	*graphValues;
	sUInt32 numGraphValues;
	sUInt32	curGraphPt;
	
	// draw as solid
	sBool	solidGraph;


	// mark that the parent window or hierarchy
	// has just changed size
	void sizeChanged();

	// draw the label
	void draw(HDC hdc);


	// add a value to the graph
	void addValue(sFloat newval);

	// static funtions callable via the control namespace
	static void registerThis(HINSTANCE hInstance);
	static void unregisterThis(HINSTANCE hInstance);
};

// common creation and destruction functions for this control
cNinjaGraph *createNinjaGraph(HWND hwHost, sFloat min, sFloat max, sBool solid = FALSE);
void destroyNinjaGraph(HWND hwHost);
cNinjaGraph *getNinjaGraph(HWND hwHost);


#endif
