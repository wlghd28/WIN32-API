// Win32Api_Custom.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_Custom.h"

#define MAX_LOADSTRING 100
#define STARTCLOCK 999

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
CHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
CHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
static CONST CHAR AppTitle[] = "WIN32 GUI - 탁상시계";
HBITMAP hBtm_Bkgnd;

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
    LoadString(hInstance, IDC_WIN32APICUSTOM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APICUSTOM));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APICUSTOM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WIN32APICUSTOM);
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
   Regist7Segment();
   RegistBlank();
   HWND hWnd = CreateWindow(szWindowClass, AppTitle, WS_OVERLAPPEDWINDOW,
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
        InitBitmap(hWnd);
        SetTimer(hWnd, STARTCLOCK, 1000, NULL);
        PostMessage(hWnd, WM_TIMER, STARTCLOCK, 0);
        break;
    case WM_TIMER:
        WM_Timer(hWnd, message, wParam, lParam);
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
        DestroyBitmap(hWnd);
        KillTimer(hWnd, STARTCLOCK);
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

  
    default:
        break;
    }

}

//-----------------------------------------------------------------------------
//     TIMER 메시지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_Timer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {

    case STARTCLOCK:
    {
        SYSTEMTIME ST;

        GetLocalTime(&ST);

        //sprintf_s(Buff, "%02d", ST.wHour);
        //SetDlgItemText(hWnd, SEVENSEGMENT1ID, Buff);

        //sprintf_s(Buff, "%02d", ST.wMinute);
        //SetDlgItemText(hWnd, SEVENSEGMENT2ID, Buff);

        SendDlgItemMessage(hWnd, SEVENSEGMENT1ID, SSM_SETVALUE, ST.wHour, 0);
        SendDlgItemMessage(hWnd, SEVENSEGMENT2ID, SSM_SETVALUE, ST.wMinute, 0);
        SendDlgItemMessage(hWnd, SEVENSEGMENT3ID, SSM_SETVALUE, ST.wSecond, 0);

        SendDlgItemMessage(hWnd, BLANK1ID, BLM_UPDATE, 0, 0);
        SendDlgItemMessage(hWnd, BLANK2ID, BLM_UPDATE, 0, 0);

    }
        break;
    default:
        break;
    }
  
}



//-----------------------------------------------------------------------------
//      커스텀 컨트롤 생성
//-----------------------------------------------------------------------------
void WINAPI CreateControl(HWND hWnd)
{
    CreateWindow("7SEGMENT", "WOOD.BMP 7SegMentBigGreen.bmp 140 187", WS_CHILD | WS_VISIBLE,
        10, 80, 280, 187, hWnd, (HMENU)SEVENSEGMENT1ID, hInst, NULL);

    CreateWindow("7SEGMENT", "WOOD.BMP 7SegMentBigRed.bmp 140 187", WS_CHILD | WS_VISIBLE,
        360, 80, 280, 187, hWnd, (HMENU)SEVENSEGMENT2ID, hInst, NULL);

    CreateWindow("7SEGMENT", "WOOD.BMP 7SegMentBigRed.bmp 140 187", WS_CHILD | WS_VISIBLE,
        710, 80, 280, 187, hWnd, (HMENU)SEVENSEGMENT3ID, hInst, NULL);

    CreateWindow("BLANK", "WOOD.BMP 7SegMentBigGreen.bmp 70 187", WS_CHILD | WS_VISIBLE,
        290, 80, 70, 187, hWnd, (HMENU)BLANK1ID, hInst, NULL);

    CreateWindow("BLANK", "WOOD.BMP 7SegMentBigRed.bmp 70 187", WS_CHILD | WS_VISIBLE,
        640, 80, 70, 187, hWnd, (HMENU)BLANK2ID, hInst, NULL);

}


//-----------------------------------------------------------------------------
//      비트맵 이미지 초기화
//-----------------------------------------------------------------------------
void WINAPI InitBitmap(HWND hWnd)
{
    hBtm_Bkgnd = LoadBitmapFile("WOOD.BMP");
    if (hBtm_Bkgnd == NULL) MessageBox(hWnd, "배경이미지 로드 실패!", "Error", MB_ICONERROR);
}

//-----------------------------------------------------------------------------
//      비트맵 이미지 해제
//-----------------------------------------------------------------------------
void WINAPI DestroyBitmap(HWND hWnd)
{
    if (hBtm_Bkgnd != NULL)     DeleteObject(hBtm_Bkgnd);
}

//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static void WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    //HBITMAP hBtm;
    RECT R;

    GetClientRect(hWnd, &R);

    DrawBitmap(hDC, 0, 0, R.right, R.bottom, hBtm_Bkgnd, 0, 0, SRCCOPY);

    //DrawBitmap(hDC, 290, 80, 70, 187, hBtm_7SegMent, 140 * 10 + 0, 187, SRCAND);
    //DrawBitmap(hDC, 290, 80, 70, 187, hBtm_7SegMent, 140 * 10 + 0, 0, SRCPAINT); 
}

