///////////////////////////////////////////////////////////////////////////////
//                  API강의 - 그래픽 hDC
//
// 시작일:
// 프로그래머:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>    //wvnsprintf()
#define SCREENDEBUG 1
#include <stdio.h>

static CONST CHAR AppTitle[]="WIN32 메인 윈도우 창 템플릿";
static CONST CHAR MainWindowClassName[]="MainWnd";





//-----------------------------------------------------------------------------
//       hBitmap을 그림
//-----------------------------------------------------------------------------
VOID WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
                       HBITMAP hBtm, int SrcX, int SrcY)
    {
    HDC hMemDC;

    hMemDC=CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBtm);
    BitBlt(hDC, DestX, DestY, Width, Height, hMemDC, SrcX, SrcY, SRCCOPY);
    DeleteDC(hMemDC);
    }




HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName)
    {
    return (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }



//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
    {
    HPEN hPenOld;
    HBRUSH hBrOld;
    HBITMAP hBtm;
    static CONST CHAR DispText[]="메인 윈도우 입니다.";

    TextOut(hDC, 0,0, DispText, lstrlen(DispText));

    //팬사용
    hPenOld=(HPEN)SelectObject(hDC, CreatePen(PS_DASHDOTDOT, 1, RGB(255,0,0)));
    MoveToEx(hDC, 100, 100, NULL);
    LineTo(hDC, 200, 200);
    DeleteObject(SelectObject(hDC, hPenOld));

    //브러시사용
    hBrOld=(HBRUSH)SelectObject(hDC, CreateSolidBrush(RGB(0,255,0)));
    SelectObject(hDC, GetStockObject(NULL_PEN));
    Ellipse(hDC, 100,100, 400,400);
    DeleteObject(SelectObject(hDC, hBrOld));

    if ((hBtm=LoadBitmapFile("LSK.BMP"))!=NULL)
        {
        DrawBitmap(hDC, 500, 10, 200, 200, hBtm, 50,50);
        }
    }



//-----------------------------------------------------------------------------
//      메인 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //printf("Msg=%X\n", Msg);

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

        case WM_SIZE:           //윈도우 크기의 변화가 생겼을 때
                                //LOWORD(lPrm): Client Width, HIWORD(lPrm): Client Height
            goto Ret0;

        case WM_COMMAND:        //메뉴를 클릭했을 때
            goto Ret0;

        case WM_KEYDOWN:        //키를 눌렀을 때
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
    WC.lpfnWndProc=MainWndProc;
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
                      CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                      (HWND)NULL, (HMENU)NULL, hInst, NULL);

    ShowWindow(hWnd, CmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&M, 0, 0, 0))
        {
        TranslateMessage(&M);
        DispatchMessage(&M);
        }

    return M.wParam;
    }



int main()
    {
    return WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOW);
    }


