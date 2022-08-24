/*
    프로젝트 속성의 링크 옵션 항목에 따라서 프로그램이 실행될 때 호출되는 첫 진입점이 달라짐.
    /SUBSYSTEM:CONSOLE => mainCRTStartup / wmainCRTStartup => main / wmain
    /SUBSYSTEM:WINDOWS => WinMainCRTStartup / wWinMainCRTStartup => WinMain / wWinMain
    /DLL => _DllMainCRTStartup => DllMain

    빈 프로젝트로 프로젝트를 생성 했을 때 WINAPI 함수를 쓸 때 헤더파일을 포함 시켰는데도 LNK2019 오류가 난다면
    Visual Studio의 최신 표준 라이브러리 변경에 의해 추가해야 할 라이브러리들이 추가됐기 때문이다.
    따라서 msvcrt.lib, ucrt.lib, vcruntime.lib 3개의 라이브러리를 추가 종속성에 추가 시켜줘야 한다.
*/

//// Win32Api_Base.cpp
#include "Win32Api_Base.h"

// 전역변수
static CONST CHAR AppTitle[] = "WIN32 메인 윈도우 창 템플릿";
static CONST CHAR MainWindowClassName[] = "MainWnd";

static CONST CHAR DispText[] = "메인 윈도우 입니다.";
static int TextPosX, TextPosY;

//--------------------------------------------------------------------------------------
//  윈도우 어플리케이션 메인
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    //wc.cbClsExtra = 0;
    //wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //wc.lpszMenuName = MAKEINTRESOURCE(MainMenuID);
    wc.lpszClassName = MainWindowClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wc);

    hWnd = CreateWindow
    (
        MainWindowClassName,
        AppTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        (HMENU)NULL,
        hInst,
        NULL
    );

    ShowWindow(hWnd, CmdShow);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


//--------------------------------------------------------------------------------------
//  VC로 컴파일 했을 때 실행파일에서 제일 먼저 호출되는 함수.

//  프로젝트 속성의 링크 옵션에서 /NODEFAULTLIB 를 주어야 호출됨.

//  C-Runtime 라이브러리의 불일치 때문에 에러가 날 경우 
//  프로젝트 속성으로 이동하여 구성 속성 > C/C++ > 모든 옵션 > 기본 런타임 검사 옵션을 '기본값'으로 설정한다.

//  __security_init_cookie 함수호출로 인한 전역 보안 쿠키 /GS(버퍼 보안 검사) 에러가 날 경우 
//  프로젝트 속성으로 이동하여 구성 속성 > C/C++ > 모든 옵션 > 보안검사 옵션을 '사용안함'으로 설정한다.
//--------------------------------------------------------------------------------------
int WinMainCRTStartup(void)
{
    int iRet;
    STARTUPINFO SI;
    SI.dwFlags = 0;
    GetStartupInfo(&SI);
    iRet = WinMain
    (
        GetModuleHandle(0),
        0,
        GetCommandLine(),
        SI.dwFlags & STARTF_USESHOWWINDOW ? SI.wShowWindow : SW_SHOWDEFAULT
    );

    ExitProcess(iRet);

    return iRet;
}


//--------------------------------------------------------------------------------------
//  스크린 디버그 함수
//--------------------------------------------------------------------------------------
void Printf(LPCSTR FormStr, ...)  // 스크린 디버그 함수 (가변인자)
{
    HDC hDC;
    va_list VL;
    CHAR Buff[MAX_PATH];
    static int DebugPosY = 0;

    va_start(VL, FormStr);
    StringCbPrintf(Buff, sizeof(Buff), FormStr, VL);
    va_end(VL);

    hDC = GetDC(NULL);
    TextOut(hDC, 0, DebugPosY, Buff, lstrlen(Buff));
    if ((DebugPosY += 16) >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;

    //OutputDebugString(Buff);
}

//--------------------------------------------------------------------------------------
//  윈도우 메시지 처리 함수
//--------------------------------------------------------------------------------------
static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_CREATE:         // 윈도우가 생성될 때 한번 옴
        break;

    case WM_DESTROY:        //윈도우가 파기될 때
        PostQuitMessage(0); //GetMessage()의 리턴을 FALSE로 만들어 종료하게 함
        break;

    case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
    {
        PAINTSTRUCT PS;
        BeginPaint(hWnd, &PS);
        DrawAll(hWnd, PS.hdc);
        EndPaint(hWnd, &PS);
    }
        break;

    case WM_LBUTTONDOWN:
        DragStart(hWnd, lPrm);
        break;

    case WM_LBUTTONUP:
        DragFinish(hWnd, lPrm);
        break;

    case WM_MOUSEMOVE:
        DragMoving(hWnd, lPrm);
        break;



    case WM_SIZE:
        break;

    case WM_COMMAND:
        //WM_Proc(wPrm, lPrm);
        break;

    case WM_KEYDOWN:
        break;
    }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
}


//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static void WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    TextOut(hDC, TextPosX, TextPosY, DispText, lstrlen(DispText));
}


static void WINAPI DrawDrag(HWND hWnd, COLORREF Col)
{
    HDC hDC;

    hDC = GetDC(hWnd);
    SetTextColor(hDC, Col);
    DrawAll(hWnd, hDC);
    ReleaseDC(hWnd, hDC);
}




//-----------------------------------------------------------------------------
//      드래그 시작 (WM_LBUTTONDOWN)
//-----------------------------------------------------------------------------
void WINAPI DragStart(HWND hWnd, LPARAM lPrm)
{
    HDC hDC;
    SIZE S;
    RECT R;
    POINT P;

    hDC = GetDC(hWnd);
    GetTextExtentPoint(hDC, DispText, lstrlen(DispText), &S);
    ReleaseDC(hWnd, hDC);

    P.x = LOWORD(lPrm);
    P.y = HIWORD(lPrm);

    SetRect(&R, TextPosX, TextPosY, TextPosX + S.cx, TextPosY + S.cy);
    if (PtInRect(&R, P) != FALSE)
    {
        SetCapture(hWnd);
    }
}



//-----------------------------------------------------------------------------
//      드래그 종료 (WM_LBUTTONUP)
//-----------------------------------------------------------------------------
void WINAPI DragFinish(HWND hWnd, LPARAM lPrm)
{
    if (GetCapture() == hWnd)
    {
        DrawDrag(hWnd, RGB(255, 255, 255));
        TextPosX = LOWORD(lPrm);
        TextPosY = HIWORD(lPrm);
        DrawDrag(hWnd, RGB(0, 0, 0));

        ReleaseCapture();
    }
}



//-----------------------------------------------------------------------------
//      드래그 이동 (WM_MOUSEMOVE)
//-----------------------------------------------------------------------------
void WINAPI DragMoving(HWND hWnd, LPARAM lPrm)
{
    if (GetCapture() == hWnd)
    {
        DrawDrag(hWnd, RGB(255, 255, 255));
        TextPosX = LOWORD(lPrm);
        TextPosY = HIWORD(lPrm);
        DrawDrag(hWnd, RGB(255, 0, 0));
    }
}



