
#include "ninjaFW.h"
#include "ninja.h"
#include "resource.h"

#include "oddity.h"

cNinjaLED *LEDdisplay = NULL;

//----------------------------------------------------------------------------------------------------------------------
FrameOutput g_output;
FXState     g_state;

int analogIncA, analogIncB, analogIncC;
int analogLastA, analogLastB, analogLastC;
bool shouldClick = false;

//----------------------------------------------------------------------------------------------------------------------
BOOL CALLBACK basicHostProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) 
  {
  case WM_INITDIALOG:
    {
      analogIncA = analogIncB = analogIncC = 1024;
      analogLastA = analogLastB = analogLastC = 1024;
      SendMessage(GetDlgItem(hWnd,IDC_SPIN1), UDM_SETRANGE, 0L, MAKELONG(2048, 0));
      SendMessage(GetDlgItem(hWnd,IDC_SPIN1), UDM_SETPOS, 0L, MAKELONG(1024, 0));
      SendMessage(GetDlgItem(hWnd,IDC_SPIN2), UDM_SETRANGE, 0L, MAKELONG(2048, 0));
      SendMessage(GetDlgItem(hWnd,IDC_SPIN2), UDM_SETPOS, 0L, MAKELONG(1024, 0));
      SendMessage(GetDlgItem(hWnd,IDC_SPIN3), UDM_SETRANGE, 0L, MAKELONG(2048, 0));
      SendMessage(GetDlgItem(hWnd,IDC_SPIN3), UDM_SETPOS, 0L, MAKELONG(1024, 0));


      createNinjaFrame(GetDlgItem(hWnd,IDC_FRAME1),NULL,NJALIGN_LEFT,FALSE);

      createNinjaButton(GetDlgItem(hWnd,IDC_EXITODD),NULL,NJALIGN_CENTER,FALSE);
      setBaseHeavyStyle(GetDlgItem(hWnd,IDC_EXITODD),TRUE);

      createNinjaButton(GetDlgItem(hWnd,IDC_CLICKER),NULL,NJALIGN_CENTER,FALSE);

      LEDdisplay = createNinjaLED(GetDlgItem(hWnd,IDC_LED), Constants::FrameWidth);

      ::SetWindowPos(GetDlgItem(hWnd,IDC_LED), NULL, 0, 0, (14 * Constants::FrameWidth) + 10, (14 * Constants::FrameHeight) + 10, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

      SetTimer(hWnd, 0x01, 4, NULL);

      g_output.clear();
      vfx::init(g_state);
    }
    break;

  case WM_HSCROLL:
  case WM_VSCROLL:
    {
      if ((HWND)(lParam) == GetDlgItem(hWnd,IDC_SPIN1))
      {
        analogIncA = HIWORD(wParam);
      }
      else if ((HWND)(lParam) == GetDlgItem(hWnd,IDC_SPIN2))
      {
        analogIncB = HIWORD(wParam);
      }
      else if ((HWND)(lParam) == GetDlgItem(hWnd,IDC_SPIN3))
      {
        analogIncC = HIWORD(wParam);
      }
    }
    break;

  case WM_TIMER:
    {
      //g_output.clear();
      g_state.counter ++;

      // work out changes from the encoders
      FrameInput inputs;
      int alA = analogIncA;
      int alB = analogIncB;
      int alC = analogIncC;  
      inputs.dialChange[0] = (alA - analogLastA);
      inputs.dialChange[1] = (alB - analogLastB);
      inputs.dialChange[2] = (alC - analogLastC);
      inputs.dialClick = shouldClick;
      analogLastA = alA;
      analogLastB = alB;
      analogLastC = alC;

      shouldClick = false;


      vfx::tick(inputs, g_state, g_output);

      LEDdisplay->decodeFramebuffer(g_output.frame);

      InvalidateRect(LEDdisplay->hwHost, 0, FALSE);
    }
    break;


  case WM_NINJA_BUTTON:
    {
      switch(lParam)
      {
      case IDC_EXITODD:
        EndDialog(hWnd,0);
        break;

      case IDC_CLICKER:
        shouldClick = true;
        break;

      }
    }
    break;

  default:
    return FALSE;
  }
  return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(	HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpcmdline,
  int ncmdshow)
{
  InitNinjaControls(hInstance,NULL);

  DialogBox(
    hInstance,
    MAKEINTRESOURCE(IDD_HOST),
    GetDesktopWindow(),
    basicHostProc);

  return 0;
}

