#include "framework.h"
#include "Blank.h"



//-----------------------------------------------------------------------------
//      Blank 그려주는 함수
//-----------------------------------------------------------------------------
static void WINAPI DrawBlank(HWND hWnd, HDC hDC, BLANK* BLK)
{
    //int Value;
    RECT  R;
    POINT P;

    if (BLK->hBtmBkgnd != NULL)
    {
        GetWindowRect(hWnd, &R);
        P.x = R.left; P.y = R.top;
        ScreenToClient(GetParent(hWnd), &P);

        GetClientRect(hWnd, &R);
        DrawBitmap(hDC, 0, 0, R.right, R.bottom, BLK->hBtmBkgnd, P.x, P.y, SRCCOPY);
    }

    if (BLK->hBtmBlank != NULL)
    {
        DrawBitmap(hDC, 0, 0, BLK->DigitWidth, BLK->DigitHeight, BLK->hBtmBlank, BLK->DigitWidth * 2 * 10, BLK->DigitHeight, SRCAND);    //S &= B;     //힌색 0xFFFFFF 검정색 0x000000
        DrawBitmap(hDC, 0, 0, BLK->DigitWidth, BLK->DigitHeight, BLK->hBtmBlank, BLK->DigitWidth * 2 * 10, 0, SRCPAINT);
    }
}



//-----------------------------------------------------------------------------
//      Blank 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT CALLBACK BlankWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    LPSTR lpWidth, lpHeight, BlkFName;
    CHAR Buff[MAX_PATH];
    BLANK* BLK;    // 구조체 포인터를 전역변수로 하면 생성한 두 개의 커스텀 컨트롤이 같은 메모리의 주소를 공유하기 때문에 치명적인 문제가 발생한다.
                   // 따라서, 전역변수가 아닌 각자의 윈도우 클래스의 cbWndExtra 멤버변수에 구조체 포인터를 저장해놓고 사용한다.

    BLK = (BLANK*)GetWindowLong(hWnd, 0);    // 윈도우 클래스의 cbWndExtra 멤버변수에 저장되어 있는 BLANK* 포인터를 가져온다.
    switch (Msg)
    {
    case WM_CREATE:         //윈도우가 생성될 때 한번 옴
        BLK = (BLANK*)LocalAlloc(LMEM_FIXED, sizeof(BLANK));
        SetWindowLong(hWnd, 0, (LONG)BLK);  // 윈도우 클래스의 cbWndExtra 멤버변수에 BLANK* 포인터를 저장해놓는다.

        if (BLK != NULL)
        {
            ZeroMemory(BLK, sizeof(BLANK));
            GetWindowText(hWnd, Buff, sizeof(Buff));
            BlkFName = StrChr(Buff, ' ');
            BlkFName[0] = 0;
            BlkFName++;

            lpWidth = StrChr(BlkFName, ' ');
            lpWidth[0] = 0;
            lpWidth++;

            lpHeight = StrChr(lpWidth, ' ') + 1;

            BLK->DigitWidth = StrToInt(lpWidth);
            BLK->DigitHeight = StrToInt(lpHeight);

            BLK->hBtmBkgnd = LoadBitmapFile(Buff);
            BLK->hBtmBlank = LoadBitmapFile(BlkFName);
        }
        break;

    case WM_DESTROY:        //윈도우가 파기될 때
        if (BLK != NULL)
        {
            if (BLK->hBtmBkgnd != NULL) DeleteObject(BLK->hBtmBkgnd);
            if (BLK->hBtmBlank != NULL) DeleteObject(BLK->hBtmBlank);
            LocalFree(BLK);
        }
        break;

    case BLM_UPDATE:
        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_SETTEXT:
        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
    {
        PAINTSTRUCT PS;

        BeginPaint(hWnd, &PS);
        if (BLK != NULL) DrawBlank(hWnd, PS.hdc, BLK);
        EndPaint(hWnd, &PS);
        break;
    }

    default:
        break;
    }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
}


//-----------------------------------------------------------------------------
//       Blank 윈도우 등록
//-----------------------------------------------------------------------------
void WINAPI RegistBlank()
{
    WNDCLASSEX WC;

    ZeroMemory(&WC, sizeof(WC));
    WC.cbSize = sizeof(WC);
    WC.style = CS_HREDRAW | CS_VREDRAW;
    WC.lpfnWndProc = BlankWndProc;
    //WC.cbClsExtra=0;
    WC.cbWndExtra = sizeof(BLANK*);
    WC.hInstance = hInst;
    WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    WC.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //WC.lpszMenuName=MAKEINTRESOURCE(MainMenuID);
    WC.lpszClassName = "BLANK";
    WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WC);
}


