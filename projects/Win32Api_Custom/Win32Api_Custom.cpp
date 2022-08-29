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

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);


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
        //CreateControl(hWnd);
        CreateWindow("7SEGMENT", "23", WS_CHILD | WS_VISIBLE,
            10, 80, 280, 187, hWnd, (HMENU)SEVENSEGMENT1ID, hInst, NULL);

        CreateWindow("7SEGMENT", "59", WS_CHILD | WS_VISIBLE,
            360, 80, 280, 187, hWnd, (HMENU)SEVENSEGMENT2ID, hInst, NULL);

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
        CHAR Buff[4];
        SYSTEMTIME ST;

        GetLocalTime(&ST);

        //SetWindowLong(GetDlgItem(hWnd, SEVENSEGMENT1ID), 0, ST.wHour);
        //InvalidateRect(GetDlgItem(hWnd, SEVENSEGMENT1ID), NULL, FALSE);

        sprintf(Buff, "%02d", ST.wHour);
        SetDlgItemText(hWnd, SEVENSEGMENT1ID, Buff);
        //printf("%d\n", ST.wHour);
        //SetWindowLong(GetDlgItem(hWnd, SEVENSEGMENT2ID), 0, ST.wMinute);
        //InvalidateRect(GetDlgItem(hWnd, SEVENSEGMENT2ID), NULL, FALSE);

        sprintf(Buff, "%02d", ST.wMinute);
        SetDlgItemText(hWnd, SEVENSEGMENT2ID, Buff);
        //printf("%d\n", ST.wMinute);
    }
        break;
    default:
        break;
    }
  
}

//-----------------------------------------------------------------------------
//      7 Segment 윈도우 등록
//-----------------------------------------------------------------------------
void WINAPI Regist7Segment()
{
    WNDCLASSEX WC;

    ZeroMemory(&WC, sizeof(WC));
    WC.cbSize = sizeof(WC);
    WC.style = CS_HREDRAW | CS_VREDRAW;
    WC.lpfnWndProc = SevenSegmentWndProc;
    //WC.cbClsExtra=0;
    WC.cbWndExtra = sizeof(int);
    WC.hInstance = hInst;
    WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    WC.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //WC.lpszMenuName=MAKEINTRESOURCE(MainMenuID);
    WC.lpszClassName = "7SEGMENT";
    WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WC);
}




//-----------------------------------------------------------------------------
//      7-세그먼드 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_CREATE:         //윈도우가 생성될 때 한번 옴
        break;

    case WM_DESTROY:        //윈도우가 파기될 때
        break;

    case WM_SETTEXT:        // SetDlgItemInt(hWnd, ID...); 함수 호출 하면 날아오는 메시지
        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
    {
        PAINTSTRUCT PS;

        BeginPaint(hWnd, &PS);
        DrawSevenSegment(hWnd, PS.hdc);
        EndPaint(hWnd, &PS);
        break;
    }
    }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
}






//-----------------------------------------------------------------------------
//      컨트롤 생성
//-----------------------------------------------------------------------------
void WINAPI CreateControl(HWND hWnd)
{
  
}



//-----------------------------------------------------------------------------
//          비트맵 파일을 로딩함
//-----------------------------------------------------------------------------
HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName)
{
    return (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}



//-----------------------------------------------------------------------------
//       hBitmap을 그림
//-----------------------------------------------------------------------------
void WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY, int CopyMode)
{
    HDC hMemDC;

    hMemDC = CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBtm);
    BitBlt(hDC, DestX, DestY, Width, Height, hMemDC, SrcX, SrcY, CopyMode);
    DeleteDC(hMemDC);
}



//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static void WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    HBITMAP hBtm;
    RECT R;

    GetClientRect(hWnd, &R);
    if ((hBtm = LoadBitmapFile("WOOD.BMP")) != NULL)
    {
        DrawBitmap(hDC, 0, 0, R.right, R.bottom, hBtm, 0, 0, SRCCOPY);
        DeleteObject(hBtm);
    }

    if ((hBtm = LoadBitmapFile("7SegMentBigRed.bmp")) != NULL)
    {
        DrawBitmap(hDC, 290, 80, 70, 187, hBtm, 140 * 10 + 0, 187, SRCAND);
        DrawBitmap(hDC, 290, 80, 70, 187, hBtm, 140 * 10 + 0, 0, SRCPAINT);
        DeleteObject(hBtm);
    }
}




//-----------------------------------------------------------------------------
//          7-Segment 그려주는 함수
//-----------------------------------------------------------------------------
static void WINAPI DrawSevenSegment(HWND hWnd, HDC hDC)
{
    //int Value;
    RECT  R;
    POINT P;
    HBITMAP hBtm;
    CHAR Buff[4];

    if ((hBtm = LoadBitmapFile("WOOD.BMP")) != NULL)
    {
        GetWindowRect(hWnd, &R);
        P.x = R.left; P.y = R.top;
        ScreenToClient(GetParent(hWnd), &P);

        GetClientRect(hWnd, &R);
        DrawBitmap(hDC, 0, 0, R.right, R.bottom, hBtm, P.x, P.y, SRCCOPY);
        DeleteObject(hBtm);
    }

    if ((hBtm = LoadBitmapFile("7SegMentBigRed.bmp")) != NULL)
    {
        //Value=GetWindowLong(hWnd, 0);
        GetWindowText(hWnd, Buff, sizeof(Buff));
        //printf("%s\n", Buff);

        DrawBitmap(hDC, 0, 0, 140, 187, hBtm, 140 * (Buff[0] - '0'), 187, SRCAND);    //S &= B;     //힌색 0xFFFFFF 검정색 0x000000
        DrawBitmap(hDC, 0, 0, 140, 187, hBtm, 140 * (Buff[0] - '0'), 0, SRCPAINT);

        DrawBitmap(hDC, 140, 0, 140, 187, hBtm, 140 * (Buff[1] - '0'), 187, SRCAND);
        DrawBitmap(hDC, 140, 0, 140, 187, hBtm, 140 * (Buff[1] - '0'), 0, SRCPAINT);

        DeleteObject(hBtm);
    }
}


