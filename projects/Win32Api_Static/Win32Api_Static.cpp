﻿// Win32Api_Static.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_Static.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
CHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
CHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
static CONST CHAR AppTitle[] = "콤보박스와 리스트박스 활용";

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 매크로 함수 정의
#define CREATEBUTTON(Title, Style, X,Y, SX, SY, hWnd, ID)       \
    CreateWindow("BUTTON", Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \

#define CREATESTATIC(Title, Style, X,Y, SX, SY, hWnd, ID)       \
    CreateWindow("STATIC", Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \



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
    LoadString(hInstance, IDC_WIN32APISTATIC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APISTATIC));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APISTATIC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WIN32APISTATIC);
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

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;

    case IDC_GETDATE:
    {
        CHAR Buff[80];
        SYSTEMTIME st;

        SendDlgItemMessage(hWnd, IDC_DATETIME, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
        wsprintf(Buff, "%d-%d-%d", st.wYear, st.wMonth, st.wDay);
        MessageBox(hWnd, Buff, AppTitle, MB_OK);
    }
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
    CREATESTATIC("", SS_SUNKEN, 10, 10, 300, 2, hWnd, -1);
    CREATESTATIC("타이틀", SS_SUNKEN | SS_CENTER, 10, 20, 300, 20, hWnd, -1);
    CREATESTATIC("", SS_ETCHEDFRAME, 10, 50, 300, 20, hWnd, -1);

    CREATESTATIC("", SS_ICON, 10, 100, 32, 32, hWnd, PhoneBookStatic1SSID);
    CREATEBUTTON("그룹", BS_GROUPBOX, 10, 150, 300, 50, hWnd, -1);

    SendDlgItemMessage(hWnd, PhoneBookStatic1SSID, STM_SETICON, (WPARAM)LoadIcon(NULL, IDI_QUESTION), 0);

    CreateWindow("SysDateTimePick32", "", WS_CHILD | WS_VISIBLE, 
        10, 220, 100, 20, 
        hWnd, (HMENU)(IDC_DATETIME), hInst, NULL);



    CREATEBUTTON("GetDate", 0, 10, 250, 100, 20, hWnd, IDC_GETDATE);

}
