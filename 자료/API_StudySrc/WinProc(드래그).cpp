///////////////////////////////////////////////////////////////////////////////
//                      WIN32 메인 윈도우 창
//
// 시작일:
// 프로그래머:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>    //wvnsprintf()


static CONST CHAR AppTitle[]="WIN32 메인 윈도우 창 템플릿";
static CONST CHAR MainWindowClassName[]="MainWnd";


static CONST CHAR DispText[]="메인 윈도우 입니다.";
static int TextPosX, TextPosY;



//-----------------------------------------------------------------------------
//      스크린 디버그 함수
//-----------------------------------------------------------------------------
#pragma comment(lib, "Shlwapi.lib")
VOID Printf(LPCSTR FormStr, ...)
    {
    HDC  hDC;
    va_list VL;
    CHAR Buff[MAX_PATH];
    static int  DebugPosY=0;

    va_start(VL, FormStr);
    wvnsprintf(Buff, sizeof(Buff), FormStr, VL);
    va_end(VL);

    hDC=GetDC(NULL);
    TextOut(hDC, 0, DebugPosY, Buff, lstrlen(Buff));
    ReleaseDC(NULL, hDC);
    if ((DebugPosY+=16)>=GetSystemMetrics(SM_CYSCREEN)) DebugPosY=0;

    //DebugFile("%s\r\n",Buff);
    //OutputDebugString(Buff);
    }




//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
    {
    TextOut(hDC, TextPosX, TextPosY, DispText, lstrlen(DispText));
    }


static VOID WINAPI DrawDrag(HWND hWnd, COLORREF Col)
    {
    HDC hDC;

    hDC=GetDC(hWnd);
    SetTextColor(hDC, Col);
    DrawAll(hWnd, hDC);
    ReleaseDC(hWnd, hDC);
    }




//-----------------------------------------------------------------------------
//      드래그 시작 (WM_LBUTTONDOWN)
//-----------------------------------------------------------------------------
VOID WINAPI DragStart(HWND hWnd, LPARAM lPrm)
    {
    HDC hDC;
    SIZE S;
    RECT R;
    POINT P;

    hDC=GetDC(hWnd);
    GetTextExtentPoint(hDC, DispText, lstrlen(DispText), &S);
    ReleaseDC(hWnd, hDC);

    P.x=LOWORD(lPrm);
    P.y=HIWORD(lPrm);

    SetRect(&R, TextPosX, TextPosY, TextPosX+S.cx, TextPosY+S.cy);
    if (PtInRect(&R, P)!=FALSE)
        {
        SetCapture(hWnd);
        }
    }



//-----------------------------------------------------------------------------
//      드래그 종료 (WM_LBUTTONUP)
//-----------------------------------------------------------------------------
VOID WINAPI DragFinish(HWND hWnd, LPARAM lPrm)
    {
    if (GetCapture()==hWnd)
        {
        DrawDrag(hWnd, RGB(255,255,255));
        TextPosX=LOWORD(lPrm);
        TextPosY=HIWORD(lPrm);
        DrawDrag(hWnd, RGB(0,0,0));

        ReleaseCapture();
        }
    }



//-----------------------------------------------------------------------------
//      드래그 이동 (WM_MOUSEMOVE)
//-----------------------------------------------------------------------------
VOID WINAPI DragMoving(HWND hWnd, LPARAM lPrm)
    {
    if (GetCapture()==hWnd)
        {
        DrawDrag(hWnd, RGB(255,255,255));
        TextPosX=LOWORD(lPrm);
        TextPosY=HIWORD(lPrm);
        DrawDrag(hWnd, RGB(255,0,0));
        }
    }




//-----------------------------------------------------------------------------
//      메인 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //Printf("Msg=%X", Msg);

    switch (Msg)
        {
        case WM_CREATE:         //윈도우가 생성될 때 한번 옴
            Ret0:
            return 0;

        case WM_DESTROY:        //윈도우가 파기될 때
            PostQuitMessage(0); //GetMessage()의 리턴을 FALSE로 만들어 종료하게 함
            goto Ret0;

        case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
            {
            PAINTSTRUCT PS;

            BeginPaint(hWnd, &PS);
            DrawAll(hWnd, PS.hdc);
            EndPaint(hWnd, &PS);
            goto Ret0;
            }

        case WM_LBUTTONDOWN:
            DragStart(hWnd, lPrm);
            break;

        case WM_LBUTTONUP:
            DragFinish(hWnd, lPrm);
            break;

        case WM_MOUSEMOVE:
            DragMoving(hWnd, lPrm);
            break;

        case WM_COMMAND:        //메뉴를 클릭했을 때
            //WM_Proc(wPrm, lPrm);
            goto Ret0;
        }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
    }




//-----------------------------------------------------------------------------
//      윈도우 어플리케이션 메인
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
    {
    HWND hWnd;
    MSG  M;
    WNDCLASSEX WC;

    ZeroMemory(&WC, sizeof(WC));
    WC.cbSize=sizeof(WC);
    WC.style=CS_HREDRAW|CS_VREDRAW;
    WC.lpfnWndProc=(WNDPROC)MainWndProc;
    //WC.cbClsExtra=0;
    //WC.cbWndExtra=0;
    WC.hInstance=hInst;
    WC.hIcon=LoadIcon(NULL, IDI_APPLICATION);
    WC.hCursor=LoadCursor(NULL, IDC_ARROW);
    WC.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
    //WC.lpszMenuName=MAKEINTRESOURCE(MainMenuID);
    WC.lpszClassName=MainWindowClassName;
    WC.hIconSm=LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WC);

    hWnd=CreateWindow(MainWindowClassName, AppTitle, WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      NULL, (HMENU)NULL, hInst, NULL);

    ShowWindow(hWnd, CmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&M, 0, 0, 0))
        {
        TranslateMessage(&M);
        DispatchMessage(&M);
        }

    return M.wParam;
    }


