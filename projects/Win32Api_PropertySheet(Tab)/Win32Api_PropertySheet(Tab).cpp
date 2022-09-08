// Win32Api_PropertySheet(Tab).cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_PropertySheet(Tab).h"

#include "PreferColor.h"
#include "PreferEtcSet.h"
#include "PreferFont.h"
#include "PreferStartWnd.h"
#include "PreferView.h"

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
   SetPreference(NULL);

   return TRUE;
}


//-----------------------------------------------------------------------------
//      옵션설정 (확인버튼을 누르면 1, 취소버튼을 누르면 0을 리턴)
//-----------------------------------------------------------------------------
LOCAL(BOOL) SetPreference(HWND hWnd)
{
    PROPSHEETHEADER PSH;
    PROPSHEETPAGE   PSP[5];

    SetPropsheetPage(PSP, (DLGPROC)PreferColorDlgProc, PreferColorDialog);
    SetPropsheetPage(PSP + 1, (DLGPROC)PreferViewDlgProc, PreferViewDialog);
    SetPropsheetPage(PSP + 2, (DLGPROC)PreferStartWndDlgProc, PreferStartWndDialog);
    SetPropsheetPage(PSP + 3, (DLGPROC)PreferFontDlgProc, PreferFontDialog);
    SetPropsheetPage(PSP + 4, (DLGPROC)PreferEtcSetDlgProc, PreferEtcSetDialog);

    PSH.dwSize = sizeof(PROPSHEETHEADER);
    PSH.dwFlags = PSH_PROPSHEETPAGE | PSH_USEHICON; //PSH_USECALLBACK
    PSH.hwndParent = hWnd;
    PSH.hInstance = hInst;
    PSH.pszIcon = NULL;
    PSH.pszCaption = AppTitle;
    PSH.nPages = countof(PSP);
    PSH.nStartPage = PreferPropSheetPage;  //처음 보여줄 페이지
    //PSH.hIcon = (HICON)GetClassLong(hWnd, GCL_HICON);
    PSH.hIcon = (HICON)GetClassLong(hWnd, GCLP_HICON);
    //PSH.pfnCallback     = SetPropSheetPosCB;
    PSH.ppsp = PSP;
    return (BOOL)PropertySheet(&PSH);
}


//-----------------------------------------------------------------------------
//      하나의 프라퍼티창을 설정합니다
//-----------------------------------------------------------------------------
LOCAL(VOID) SetPropsheetPage(PROPSHEETPAGE* PSP, DLGPROC DlgProc, int DlgID)
{
    ZeroMemory(PSP, sizeof(PROPSHEETPAGE));
    PSP->dwSize = sizeof(PROPSHEETPAGE);
    PSP->dwFlags = 0;
    PSP->hInstance = hInst;
    PSP->pszTemplate = MAKEINTRESOURCE(DlgID);
    PSP->pfnDlgProc = DlgProc;
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





