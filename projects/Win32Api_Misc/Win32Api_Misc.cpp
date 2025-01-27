﻿// Win32Api_Misc.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_Misc.h"

#define MAX_LOADSTRING 100
#define WINDOWSIZE_WIDTH 800
#define WINDOWSIZE_HEIGHT 600

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
CHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
CHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

static CONST CHAR AppTitle[] = "WIN32 메인 윈도우 창 템플릿";
static CONST CHAR MainWindowClassName[] = "MainWnd";
static HINSTANCE HInst;
static int SBParts[] = { 400, 550, 700 };

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WIN32APIMISC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APIMISC));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = MainWndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APIMISC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WIN32APIMISC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
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

   INITCOMMONCONTROLSEX ICC;
   ICC.dwSize = sizeof(INITCOMMONCONTROLSEX);
   ICC.dwICC = ICC_WIN95_CLASSES | ICC_DATE_CLASSES | ICC_STANDARD_CLASSES | ICC_INTERNET_CLASSES;          //"SysDateTimePick32" 이것을 사용하기 위함
   InitCommonControlsEx(&ICC);  // IP Address Contorl을 사용하기 위해서 반드시 먼저 호출해줘야 하는 함수이다.
                                // 다른 프로그램에서 먼저 호출을 해도 유효하기 때문에 보통은 굳이 호출을 안해도 되지만 
                                // 해당 프로그램이 윈도우 시작 시 가장 먼저 실행이 될 경우 이 함수가 호출되어 있지 않으면 IP Address Control이 생성되지 않는다.


   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateControl(hWnd);
        break;
    case WM_COMMAND:
        WM_CmdProc(hWnd, message, wParam, lParam);
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawAll(hWnd, ps.hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


//-----------------------------------------------------------------------------
//      메인 윈도우 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int I;
    DWORD IP = 0;
    CHAR Buff[128];

    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;

       
    case ActionBTID:
        SendDlgItemMessage(hWnd, IPAddressIPID, IPM_GETADDRESS, 0, (LPARAM)&IP);
        wsprintf(Buff, "IP = %d.%d.%d.%d", IP >> 24, (IP >> 16) & 0xFF, (IP >> 8) & 0xFF, IP & 0xFF);

        I = SendDlgItemMessage(hWnd, TrackBarTBID, TBM_GETPOS, 0, 0);
        wsprintf(Buff + lstrlen(Buff), "\r\nTrack Pos = %d", I);

        MessageBox(hWnd, Buff, AppTitle, MB_OK);
       
        break;
    
    default:
        break;
    }

}

//-----------------------------------------------------------------------------
//      컨트롤 생성
//-----------------------------------------------------------------------------
void WINAPI CreateControl(HWND hWnd)
{
    CreateWindow("BUTTON", "액션", WS_CHILD | WS_VISIBLE, 10, 10, 100, 24, hWnd, (HMENU)ActionBTID, HInst, NULL);
    CreateWindow(WC_IPADDRESS, "", WS_CHILD | WS_VISIBLE, 10, 44, 200, 24, hWnd, (HMENU)IPAddressIPID, HInst, NULL);
    CreateWindow(TRACKBAR_CLASS, "", TBS_BOTTOM | WS_CHILD | WS_VISIBLE, 10, 78, 200, 32, hWnd, (HMENU)TrackBarTBID, HInst, NULL);

    SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETRANGE, FALSE, MAKELONG(0, 10));
    SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETTIC, 0, 2);
    SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETTIC, 0, 5);
    SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETTIC, 0, 7);

    CreateWindow(PROGRESS_CLASS, "", PBS_MARQUEE | WS_CHILD | WS_VISIBLE, 10, 120, 200, 22, hWnd, (HMENU)ProgressBarPBID, HInst, NULL);
    SendDlgItemMessage(hWnd, ProgressBarPBID, PBM_SETRANGE, 0, MAKELONG(0, 100));
    SendDlgItemMessage(hWnd, ProgressBarPBID, PBM_SETPOS, 70, 0);

    CreateWindow(DATETIMEPICK_CLASS, "", WS_CHILD | WS_VISIBLE, 10, 152, 200, 22, hWnd, (HMENU)DateTimePickDTPID, HInst, NULL);

    CreateWindow(STATUSCLASSNAME, "", WS_CHILD | WS_VISIBLE, 10, 184, 200, 22, hWnd, (HMENU)StatusBarSBID, HInst, NULL);
    SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETPARTS, 3, (LPARAM)SBParts);
    SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETTEXT, 0, (LPARAM)"기타 콘트롤 강의를 마칠시간이 되었습니다");
    SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETTEXT, 1, (LPARAM)"두번째");
    SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETTEXT, 2, (LPARAM)"세번째");
}


//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    RECT R;
    static CONST CHAR DispText[] = "메인 윈도우 입니다.";

    GetClientRect(hWnd, &R);
    DrawText(hDC, DispText, lstrlen(DispText), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
