
#include "framework.h"
#include "FND.h"

//-----------------------------------------------------------------------------
//          7-Segment �׷��ִ� �Լ�
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

        DrawBitmap(hDC, 0, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[0] - '0'), SSC->DigitHeight, SRCAND);    //S &= B;     //���� 0xFFFFFF ������ 0x000000
        DrawBitmap(hDC, 0, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[0] - '0'), 0, SRCPAINT);

        DrawBitmap(hDC, SSC->DigitWidth, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[1] - '0'), SSC->DigitHeight, SRCAND);
        DrawBitmap(hDC, SSC->DigitWidth, 0, SSC->DigitWidth, SSC->DigitHeight, SSC->hBtm7Seg, SSC->DigitWidth * (Buff[1] - '0'), 0, SRCPAINT);
    }
}





//-----------------------------------------------------------------------------
//      7-���׸յ� ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT CALLBACK SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    LPSTR lpWidth, lpHeight, SegFName;
    CHAR Buff[MAX_PATH];
    SEVENSEGMENT_CTX* SSC;    // ����ü �����͸� ���������� �ϸ� ������ �� ���� Ŀ���� ��Ʈ���� ���� �޸��� �ּҸ� �����ϱ� ������ ġ������ ������ �߻��Ѵ�.
                              // ����, ���������� �ƴ� ������ ������ Ŭ������ cbWndExtra ��������� ����ü �����͸� �����س��� ����Ѵ�.

    SSC = (SEVENSEGMENT_CTX*)GetWindowLong(hWnd, 0);    // ������ Ŭ������ cbWndExtra ��������� ����Ǿ� �ִ� SEVENSEGMENT_CTX* �����͸� �����´�.
    switch (Msg)
    {
    case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
        SSC = (SEVENSEGMENT_CTX*)LocalAlloc(LMEM_FIXED, sizeof(SEVENSEGMENT_CTX));
        SetWindowLong(hWnd, 0, (LONG)SSC);  // ������ Ŭ������ cbWndExtra ��������� SEVENSEGMENT_CTX* �����͸� �����س��´�.

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

    case WM_DESTROY:        //�����찡 �ı�� ��
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

    case WM_PAINT:          //ȭ���� �׷��� �� ������ ������ ��
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
//      7 Segment ������ ���
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



