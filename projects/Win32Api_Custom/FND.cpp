
#include "framework.h"
#include "FND.h"

//-----------------------------------------------------------------------------
//          7-Segment 그려주는 함수
//-----------------------------------------------------------------------------
static void WINAPI DrawSevenSegment(HWND hWnd, HDC hDC, SEVENSEGMENT_CTX* SSC)
{
    //int Value;
    RECT  R;
    POINT P;
    CHAR Buff[4];

    if (SSC->hBtmBkgnd != NULL)
    {
        GetWindowRect(hWnd, &R);
        P.x = R.left; P.y = R.top;
        ScreenToClient(GetParent(hWnd), &P);

        GetClientRect(hWnd, &R);
        DrawBitmap(hDC, 0, 0, R.right, R.bottom, SSC->hBtmBkgnd, P.x, P.y, SRCCOPY);
    }

    if (SSC->hBtm7Seg != NULL)
    {
        wsprintf(Buff, "%02d", SSC->Value);

        DrawBitmap(hDC, 0, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[0] - '0'), SSC->DigitHeight, SRCAND);    //S &= B;     //힌색 0xFFFFFF 검정색 0x000000
        DrawBitmap(hDC, 0, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[0] - '0'), 0, SRCPAINT);

        DrawBitmap(hDC, SSC->DigitWidth, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[1] - '0'), SSC->DigitHeight, SRCAND);
        DrawBitmap(hDC, SSC->DigitWidth, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[1] - '0'), 0, SRCPAINT);
    }
}





//-----------------------------------------------------------------------------
//      7-세그먼드 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT CALLBACK SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    LPSTR lpWidth, lpHeight, SegFName;
    CHAR Buff[MAX_PATH];
    SEVENSEGMENT_CTX* SSC;    // 구조체 포인터를 전역변수로 하면 생성한 두 개의 커스텀 컨트롤이 같은 메모리의 주소를 공유하기 때문에 치명적인 문제가 발생한다.
                              // 따라서, 전역변수가 아닌 각자의 윈도우 클래스의 cbWndExtra 멤버변수에 구조체 포인터를 저장해놓고 사용한다.

    SSC = (SEVENSEGMENT_CTX*)GetWindowLong(hWnd, 0);    // 윈도우 클래스의 cbWndExtra 멤버변수에 저장되어 있는 SEVENSEGMENT_CTX* 포인터를 가져온다.
    switch (Msg)
    {
    case WM_CREATE:         //윈도우가 생성될 때 한번 옴
        SSC = (SEVENSEGMENT_CTX*)LocalAlloc(LMEM_FIXED, sizeof(SEVENSEGMENT_CTX));
        SetWindowLong(hWnd, 0, (LONG)SSC);  // 윈도우 클래스의 cbWndExtra 멤버변수에 SEVENSEGMENT_CTX* 포인터를 저장해놓는다.

        if (SSC != NULL)
        {
            ZeroMemory(SSC, sizeof(SEVENSEGMENT_CTX));

            GetWindowText(hWnd, Buff, sizeof(Buff));
            SegFName = StrChr(Buff, ' ');
            SegFName[0] = 0;
            SegFName++;

            lpWidth = StrChr(SegFName, ' ');
            lpWidth[0] = 0;
            lpWidth++;

            lpHeight = StrChr(lpWidth, ' ') + 1;

            SSC->DigitWidth = StrToInt(lpWidth);
            SSC->DigitHeight = StrToInt(lpHeight);

            SSC->hBtmBkgnd = LoadBitmapFile(Buff);
            SSC->hBtm7Seg = LoadBitmapFile(SegFName);
        }
        break;

    case WM_DESTROY:        //윈도우가 파기될 때
        if (SSC != NULL)
        {
            if (SSC->hBtmBkgnd != NULL) DeleteObject(SSC->hBtmBkgnd);
            if (SSC->hBtm7Seg != NULL) DeleteObject(SSC->hBtm7Seg);
            LocalFree(SSC);
        }
        break;

    case WM_SETTEXT:
        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
    {
        PAINTSTRUCT PS;

        BeginPaint(hWnd, &PS);
        if (SSC != NULL) DrawSevenSegment(hWnd, PS.hdc, SSC);
        EndPaint(hWnd, &PS);
        break;
    }

    case SSM_SETVALUE:
        if (SSC != NULL)
        {
            SSC->Value = wPrm;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case SSM_GETVALUE:
        if (SSC == NULL)  break;
        return SSC->Value;
    }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
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
    WC.cbWndExtra = sizeof(SEVENSEGMENT_CTX*);
    WC.hInstance = hInst;
    WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    WC.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //WC.lpszMenuName=MAKEINTRESOURCE(MainMenuID);
    WC.lpszClassName = "7SEGMENT";
    WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WC);
}



