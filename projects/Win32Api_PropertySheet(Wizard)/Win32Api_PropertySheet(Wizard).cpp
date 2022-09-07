// Win32Api_PropertySheet(Wizard).cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_PropertySheet(Wizard).h"

#include "InputSetupFolder.h"
#include "InputStartMenuFolder.h"
#include "ReadyToInstall.h"
#include "SetupInfo.h"
#include "StartSetup.h"
#include "WaitQuitMainPgm.h"

// 메인 함수 입니다.
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    return 0;
}



//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   CreateExpert(NULL, AppTitle);

   return TRUE;
}


//-----------------------------------------------------------------------------
//      스크린 디버그 함수
//-----------------------------------------------------------------------------
VOID Printf(LPCSTR FormStr, ...)
{
    HDC  hDC;
    char szTmp[MAX_PATH];
    static int  DebugPosY = 0;

    hDC = GetDC(NULL);
    wvsprintf(szTmp, FormStr, (LPSTR)(&FormStr + 1));
    //VsprintfN(szTmp, sizeof(szTmp), FormStr, &FormStr+1);
    TextOut(hDC, 0, DebugPosY, szTmp, lstrlen(szTmp));
    ReleaseDC(NULL, hDC);

    //DebugFile("%s\r\n",szTmp);
    //OutputDebugString(szTmp);

    DebugPosY += 16;
    if (DebugPosY >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;
}




//-----------------------------------------------------------------------------
//      하나의 프라퍼티창을 설정합니다
//-----------------------------------------------------------------------------
LOCAL(VOID) SetPropertyPage(PROPSHEETPAGE* PSP, int DlgID, DLGPROC DlgProc, LPCSTR Title)
{
    ZeroMemory(PSP, sizeof(PROPSHEETPAGE));
    PSP->dwSize = sizeof(PROPSHEETPAGE);
    PSP->dwFlags = PSP_USETITLE;
    PSP->hInstance = hInst;
    PSP->pszTemplate = MAKEINTRESOURCE(DlgID);
    PSP->pszIcon = NULL;
    PSP->pfnDlgProc = DlgProc;
    PSP->pszTitle = Title;
    PSP->lParam = 0;
}



//-----------------------------------------------------------------------------
//      하나의 프라퍼티창을 설정합니다
//-----------------------------------------------------------------------------
LOCAL(int) CreateExpert(HWND hWndOwner, LPCSTR lpTitle)
{
    PROPSHEETPAGE   PSP[6];
    PROPSHEETHEADER PSH;

    SetPropertyPage(PSP + 0, SetupInfoDialog, SetupInfoDlgProc, lpTitle);
    SetPropertyPage(PSP + 1, WaitQuitMainDialog, WaitQuitMainPgmDlgProc, lpTitle);
    SetPropertyPage(PSP + 2, InputSetupFolderDialog, InputSetupFolderDlgProc, lpTitle);
    SetPropertyPage(PSP + 3, InputStartMenuNameDialog, InputStartMenuFolderDlgProc, lpTitle);
    SetPropertyPage(PSP + 4, ReadyToInstallDialog, ReadyToInstallDlgProc, lpTitle);
    SetPropertyPage(PSP + 5, StartSetupDialog, StartSetupDlgProc, lpTitle);

    PSH.dwSize = sizeof(PROPSHEETHEADER);
    PSH.dwFlags = PSH_PROPSHEETPAGE | PSH_WIZARD | PSH_NOAPPLYNOW;
    PSH.hwndParent = hWndOwner;
    PSH.pszCaption = "";
    PSH.nPages = countof(PSP);
    PSH.nStartPage = 0;
    PSH.ppsp = PSP;
    return PropertySheet(&PSH);
}

