/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Win32 utilities
 |
 | $Author: Harry Denholm $ 
 | $Revision: 2 $
 | $Date: 5/06/01 0:42 $ 
 | $Archive: /base/winUtils.cpp $
 |
\*===========================================================================*/

#include "ninjaFW.h"
#include "ninjaBase.h"


/*===========================================================================*\
 | get/set checkbox items on a window
 |
 | pass the host window handle + the resource ID
\*===========================================================================*/

sInt32	getCheckBox(HWND hw, sInt32 id) 
{
	return SendMessage( GetDlgItem(hw, id), BM_GETCHECK, 0, 0L);
}

void	setCheckBox(HWND hw, sInt32 id, BOOL b) 
{
	SendMessage( GetDlgItem(hw, id), BM_SETCHECK, b, 0L);
} 



/*===========================================================================*\
 | set the GDI default font for a given window handle
\*===========================================================================*/

static BOOL CALLBACK SetFontEnum( HWND hwnd, LPARAM lParam )
{	
	SendMessage( hwnd, WM_SETFONT, (WPARAM)lParam, MAKELONG(0, 0));
	return TRUE;
}

void setDlgFont( HWND hDlg, HFONT hFont )
{
	EnumChildWindows( hDlg, SetFontEnum, (LPARAM)hFont );
}



/*===========================================================================*\
 | move a window to be screen central on the active desktop
\*===========================================================================*/

void centerWindow( HWND hwnd ) 
{ 
    RECT rc; 
    RECT rcOwner; 
    RECT rcCenter; 
    HWND hwndOwner; 
 
    GetWindowRect(hwnd, &rc); 
 
    if (!(hwndOwner = GetWindow(hwnd, GW_OWNER))) 
        hwndOwner = GetDesktopWindow(); 
 
    GetWindowRect(hwndOwner, &rcOwner); 
 

    rcCenter.left = rcOwner.left + 
            (((rcOwner.right - rcOwner.left) - 
            (rc.right - rc.left)) 
            / 2); 
 
    rcCenter.top = rcOwner.top + 
            (((rcOwner.bottom - rcOwner.top) - 
            (rc.bottom - rc.top)) 
            / 2); 
 
    rcCenter.right = rcCenter.left + (rc.right - rc.left); 
    rcCenter.bottom = rcCenter.top + (rc.bottom - rc.top); 
  
    SetWindowPos(hwnd, NULL, rcCenter.left, rcCenter.top, 0, 0, 
            SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER); 
} 
 


/*===========================================================================*\
 | GDI drawing utility functions
 | most take a HDC target, and rectangle to draw in and some colour defs
\*===========================================================================*/

void drawColorRect( HDC hdc, RECT *rect, COLORREF face )
{
	HPEN	pNull	= CreatePen(PS_NULL,0,0);
	HBRUSH	bFace	= CreateSolidBrush(face);

	DeleteObject(SelectObject(hdc,bFace));
	DeleteObject(SelectObject(hdc,pNull));
	Rectangle(hdc,rect->left,rect->top,rect->right,rect->bottom);
	DeleteObject(bFace);
	DeleteObject(pNull);
}

void drawShadedRect( HDC hdc, RECT *rect, bool in, COLORREF face )
{
	HPEN	pLight	= CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DHILIGHT)); 
	HPEN	pDark	= CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DSHADOW));
	HBRUSH	bFace	= CreateSolidBrush(face);

	DeleteObject(SelectObject(hdc,bFace));
	DeleteObject(SelectObject(hdc,in?pDark:pLight));

	// draw main rect area with light pen
	Rectangle(hdc,rect->left,rect->top,rect->right,rect->bottom);

	DeleteObject(SelectObject(hdc,in?pLight:pDark));

	// lower edges
	MoveToEx(hdc,rect->left,rect->bottom-1,NULL);
	LineTo(hdc,rect->right-1,rect->bottom-1);
	LineTo(hdc,rect->right-1,rect->top);

	DeleteObject(bFace);
	DeleteObject(pLight);
	DeleteObject(pDark);
}


void drawShadedVertLine( HDC hdc, int x, int y0, int y1, BOOL in )
{
	HPEN hLight = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNHIGHLIGHT ) );
	HPEN hDark  = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNSHADOW ) );
	
	SelectObject( hdc, in ? hDark : hLight);
	MoveToEx( hdc, x, y0, NULL );
	LineTo( hdc, x, y1 );
	SelectObject( hdc, GetStockObject(BLACK_PEN) );
	SelectObject( hdc, in ? hLight : hDark );
	MoveToEx( hdc, x+1, y0, NULL );
	LineTo( hdc, x+1, y1 );
	
	SelectObject( hdc, GetStockObject(BLACK_PEN) );
	DeleteObject( hLight );
	DeleteObject( hDark );	
}


void drawShadedHorizLine( HDC hdc, int y, int x0, int x1, BOOL in )
{
	HPEN hLight = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNHIGHLIGHT ) );
	HPEN hDark  = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNSHADOW ) );
	
	SelectObject( hdc, in?hDark:hLight );
	MoveToEx( hdc, x0, y, NULL );
	LineTo( hdc, x1, y );
	SelectObject( hdc, GetStockObject(BLACK_PEN) );
	SelectObject( hdc, in?hLight:hDark );
	MoveToEx( hdc, x0, y+1, NULL );
	LineTo( hdc, x1, y+1 );
	
	SelectObject( hdc, GetStockObject(BLACK_PEN) );
	DeleteObject( hLight );
	DeleteObject( hDark );
}



/*===========================================================================*\
 | generic file choosing function
 |
 | fname - pointer to file name storage
 | ext - extension to use, without the dot
 | load - whether or not to treat as a loading operation or saving operation
\*===========================================================================*/

sBool chooseFile(HWND hwHost, sChar8 *fname, sChar8 *ext, sChar8 *desc, sBool load, sChar8 *title)
{
	OPENFILENAME ofn;
	sChar8 filterStr[255];
	sprintf(filterStr,"%s files (%s)\n*.%s\n\0",ext,desc,ext);
	sChar8 *filtPtr = filterStr;
	while(*filtPtr!='\0')
	{
		if(*filtPtr=='\n') *filtPtr = '\0';
		filtPtr++;
	}

	
	fname[0] = '\0';
	ofn.lStructSize = sizeof(OPENFILENAME); 
	ofn.hInstance = GetModuleHandle(NULL);
	ofn.hwndOwner = hwHost;
	ofn.lpstrFilter = filterStr;
	ofn.lpstrCustomFilter = NULL;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = fname;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; 
	ofn.lpstrTitle = title; 
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_PATHMUSTEXIST; 
	ofn.lpstrDefExt = ext; 

	// user chooses file from disk
	return load?GetOpenFileName(&ofn):GetSaveFileName(&ofn);
}



/*===========================================================================*\
 | iteratively look for files within a single level path, based on a wildcard
 | match string - 'match' can be something like "*.*", "*.txt", etc
 | 
 | provide a custom callback function to deal with found files - the files
 | provided will only ever be those matching the match string search pattern
\*===========================================================================*/

void searchForFiles( 
	sChar8 *path, 
	sChar8 *match, 
	void *(*search_callback)(sChar8 *file) )
{
	// create a path to begin searching,
	// based on <path>\\<match>
	sChar8 searchString[MAX_PATH],foundFile[MAX_PATH];
	strcpy(searchString,path);
	strcat(searchString,"\\");
	strcat(searchString,match);


	// fire up the file finder
	WIN32_FIND_DATA file;
	HANDLE          findhandle = FindFirstFile(searchString, &file);
	sBool			noMoreFiles = FALSE;

	while(findhandle != INVALID_HANDLE_VALUE&&!noMoreFiles) 
	{
		// use the input path and the found filename
		// to give a fully qualified filepath
		strcpy(foundFile,path);
		strcat(foundFile,"\\");
		strcat(foundFile,file.cFileName);

		// pass it to the callback
		search_callback(foundFile);

		// continue to search until we're out of files
		sBool res = FindNextFile(findhandle,&file);
		if(!res) noMoreFiles = (GetLastError()==ERROR_NO_MORE_FILES);
	}
}



/*===========================================================================*\
 | recurse through a directory structure from given path and pass found files
 | to the callback function. note that these files can be of any type and
 | extension, so the callback must filter them down manually
\*===========================================================================*/

void searchForFilesRecurse( 
	sChar8 *path, 
	void *(*search_callback)(sChar8 *file) )
{
	// create a path to begin searching,
	// based on <path>\\*.*
	sChar8 searchString[MAX_PATH],foundFile[MAX_PATH];
	strcpy(searchString,path);
	strcat(searchString,"\\*.*");


	// fire up the file finder
	WIN32_FIND_DATA file;
	HANDLE          findhandle = FindFirstFile(searchString, &file);
	sBool			noMoreFiles = FALSE;

	while(findhandle != INVALID_HANDLE_VALUE&&!noMoreFiles) 
	{
		// use the input path and the found filename
		// to give a fully qualified filepath
		strcpy(foundFile,path);
		strcat(foundFile,"\\");
		strcat(foundFile,file.cFileName);

		// check for directory, and recurse through if so
		if(file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// skip the . and .. directories
			if(_stricmp(file.cFileName,".") && _stricmp(file.cFileName,".."))
			{
				searchForFilesRecurse(foundFile,search_callback);
			}
		}
		else
		{
			// we have found a file we can use
			// pass it to the callback for checking
			search_callback(foundFile);
		}

		// continue to search until we're out of files
		sBool res = FindNextFile(findhandle,&file);
		if(!res) noMoreFiles = (GetLastError()==ERROR_NO_MORE_FILES);
	}
}



/*===========================================================================*\
 | generate a new console for a windows app & set it up with a decent sized
 | window buffer for text scrolling
\*===========================================================================*/

void setupWinConsole()
{
	// ask to be given a console
	AllocConsole();

	// get a handle to it
	HANDLE prsConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// use the title bar for something useful
	sChar8 conTitle[128];
	sprintf(conTitle,"Compiled on %s at %s",__DATE__,__TIME__);
	SetConsoleTitle(conTitle);

	// max out the vertical screen buffer
	// so that scrolling of off-screen content is possible
	COORD conSize;
	conSize.X = 80;

	sUInt32 maxY = 640, result = 0;
	while(!result&&maxY>0)
	{
		// try the current size
		conSize.Y = maxY;
		result = SetConsoleScreenBufferSize(prsConsole,conSize);

		// try smaller buffer until we get a viable size
		maxY -= 10;
	}
}
