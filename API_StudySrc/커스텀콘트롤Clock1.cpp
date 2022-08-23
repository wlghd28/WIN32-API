///////////////////////////////////////////////////////////////////////////////
//                  API강의 - 커스텀 콘트롤 - 탁상시계
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

static CONST CHAR AppTitle[]="WIN32 GUI - 탁상시계";
static CONST CHAR MainWindowClassName[]="MainWnd";
static HINSTANCE HInst;




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
VOID WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
                       HBITMAP hBtm, int SrcX, int SrcY, int CopyMode)
    {
    HDC hMemDC;

    hMemDC=CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBtm);
    BitBlt(hDC, DestX, DestY, Width, Height, hMemDC, SrcX, SrcY, CopyMode);
    DeleteDC(hMemDC);
    }




//-----------------------------------------------------------------------------
//          7-Segment 그려주는 함수
//-----------------------------------------------------------------------------
static VOID WINAPI DrawSevenSegment(HWND hWnd, HDC hDC)
    {
    //int Value;
    RECT  R;
    POINT P;
    HBITMAP hBtm;
    CHAR Buff[4];

    if ((hBtm=LoadBitmapFile("WOOD.BMP"))!=NULL)
        {
        GetWindowRect(hWnd, &R);
        P.x=R.left; P.y=R.top;
        ScreenToClient(GetParent(hWnd), &P);

        GetClientRect(hWnd, &R);
        DrawBitmap(hDC, 0, 0, R.right, R.bottom, hBtm, P.x, P.y, SRCCOPY);
        DeleteObject(hBtm);
        }

    if ((hBtm=LoadBitmapFile("7SegMentBigRed.bmp"))!=NULL)
        {
        //Value=GetWindowLong(hWnd, 0);
        GetWindowText(hWnd, Buff, sizeof(Buff));
        if (Buff[1]==0)
            {
            Buff[1]=Buff[0];
            Buff[0]='0';
            Buff[2]=0;
            }

        DrawBitmap(hDC, 0, 0, 140, 187, hBtm, 140*(Buff[0]-'0'), 187, SRCAND);    //S &= B;     //힌색 0xFFFFFF 검정색 0x000000
        DrawBitmap(hDC, 0, 0, 140, 187, hBtm, 140*(Buff[0]-'0'),   0, SRCPAINT);

        DrawBitmap(hDC, 140, 0, 140, 187, hBtm, 140*(Buff[1]-'0'), 187, SRCAND);
        DrawBitmap(hDC, 140, 0, 140, 187, hBtm, 140*(Buff[1]-'0'),   0, SRCPAINT);

        DeleteObject(hBtm);
        }
    }



//-----------------------------------------------------------------------------
//      7-세그먼드 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    switch (Msg)
        {
        case WM_CREATE:         //윈도우가 생성될 때 한번 옴
            Ret0:
            return 0;

        case WM_DESTROY:        //윈도우가 파기될 때
            goto Ret0;

        case WM_SETTEXT:
            InvalidateRect(hWnd, NULL, FALSE);
            break;

        case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
            {
            PAINTSTRUCT PS;

            BeginPaint(hWnd, &PS);
            DrawSevenSegment(hWnd, PS.hdc);
            EndPaint(hWnd, &PS);
            goto Ret0;
            }
        }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
    }




//-----------------------------------------------------------------------------
//      7 Segment 윈도우 등록
//-----------------------------------------------------------------------------
VOID WINAPI Regist7Segment()
    {
    WNDCLASSEX WC;

    ZeroMemory(&WC, sizeof(WC));
    WC.cbSize=sizeof(WC);
    WC.style=CS_HREDRAW|CS_VREDRAW;
    WC.lpfnWndProc=SevenSegmentWndProc;
    //WC.cbClsExtra=0;
    WC.cbWndExtra=sizeof(int);
    WC.hInstance=HInst;
    WC.hIcon=LoadIcon(NULL, IDI_APPLICATION);
    WC.hCursor=LoadCursor(NULL, IDC_ARROW);
    WC.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    //WC.lpszMenuName=MAKEINTRESOURCE(MainMenuID);
    WC.lpszClassName="7SEGMENT";
    WC.hIconSm=LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WC);
    }





//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
    {
    HBITMAP hBtm;
    RECT R;

    GetClientRect(hWnd, &R);
    if ((hBtm=LoadBitmapFile("WOOD.BMP"))!=NULL)
        {
        DrawBitmap(hDC, 0, 0, R.right, R.bottom, hBtm, 0, 0, SRCCOPY);
        DeleteObject(hBtm);
        }

    if ((hBtm=LoadBitmapFile("7SegMentBigRed.bmp"))!=NULL)
        {
        DrawBitmap(hDC, 290, 80, 70, 187, hBtm, 140*10+0, 187, SRCAND);
        DrawBitmap(hDC, 290, 80, 70, 187, hBtm, 140*10+0, 0, SRCPAINT);
        DeleteObject(hBtm);
        }
    }


#define SEVENSEGMENT1ID 100
#define SEVENSEGMENT2ID 101



//-----------------------------------------------------------------------------
//      메인 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //printf("Msg=%X\n", Msg);

    switch (Msg)
        {
        case WM_CREATE:         //윈도우가 생성될 때 한번 옴
            CreateWindow("7SEGMENT", "23", WS_CHILD|WS_VISIBLE,
                         10,80, 280, 187, hWnd, (HMENU)SEVENSEGMENT1ID, HInst, NULL);

            CreateWindow("7SEGMENT", "59", WS_CHILD|WS_VISIBLE,
                         360,80, 280, 187, hWnd, (HMENU)SEVENSEGMENT2ID, HInst, NULL);

            SetTimer(hWnd, 1, 1000, NULL);
            PostMessage(hWnd, WM_TIMER, 1, 0);

            Ret0:
            return 0;

        case WM_TIMER:
            {
            SYSTEMTIME ST;

            GetLocalTime(&ST);

            //SetWindowLong(GetDlgItem(hWnd, SEVENSEGMENT1ID), 0, ST.wHour);
            //InvalidateRect(GetDlgItem(hWnd, SEVENSEGMENT1ID), NULL, FALSE);

            SetDlgItemInt(hWnd, SEVENSEGMENT1ID, ST.wHour, FALSE);

            //SetWindowLong(GetDlgItem(hWnd, SEVENSEGMENT2ID), 0, ST.wMinute);
            //InvalidateRect(GetDlgItem(hWnd, SEVENSEGMENT2ID), NULL, FALSE);

            SetDlgItemInt(hWnd, SEVENSEGMENT2ID, ST.wMinute, FALSE);

            goto Ret0;
            }

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

    HInst=hInst;

    Regist7Segment();

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
                      CW_USEDEFAULT, CW_USEDEFAULT, 648, 380,
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


