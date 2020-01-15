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
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /base/winUtils.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_WINUTILS_
#define	__NJFW_WINUTILS_


/*===========================================================================*\
 | set cursors to busy/normal
\*===========================================================================*/

#define CURSOR_BUSY			SetCursor(LoadCursor(NULL, IDC_WAIT));
#define CURSOR_ARROW		SetCursor(LoadCursor(NULL, IDC_ARROW));


/*===========================================================================*\
 | general Win32 dialog functions
\*===========================================================================*/

sInt32	getCheckBox(HWND hw, sInt32 id);
void	setCheckBox(HWND hw, sInt32 id, BOOL b);

void	setDlgFont( HWND hDlg, HFONT hFont );

void	centerWindow( HWND hwnd );


/*===========================================================================*\
 | generic GDI utility functions
\*===========================================================================*/

void drawColorRect( HDC hdc, RECT *rect, COLORREF face );
void drawShadedRect( HDC hdc, RECT *rect, bool in, COLORREF face = GetSysColor(COLOR_3DFACE) );
void drawShadedVertLine( HDC hdc, int x, int y0, int y1, BOOL in );
void drawShadedHorizLine( HDC hdc, int y, int x0, int x1, BOOL in );


/*===========================================================================*\
 | shell utility functions
 | check the cpp file for function descriptions
\*===========================================================================*/

sBool chooseFile(HWND hwHost, sChar *fname, sChar *ext, sChar8 *desc, sBool load, sChar8 *title = NULL);

void searchForFiles( char *path, char *match, void *(*search_callback)(char *file) );
void searchForFilesRecurse( char *path, void *(*search_callback)(char *file) );

void setupWinConsole();


#endif