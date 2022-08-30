#include "framework.h"
#include "Blank.h"



//-----------------------------------------------------------------------------
//      Blank �׷��ִ� �Լ�
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
        DrawBitmap(hDC, 0, 0, BLK->DigitWidth, BLK->DigitHeight, BLK->hBtmBlank, BLK->DigitWidth * 2 * 10, BLK->DigitHeight, SRCAND);    //S &= B;     //���� 0xFFFFFF ������ 0x000000
        DrawBitmap(hDC, 0, 0, BLK->DigitWidth, BLK->DigitHeight, BLK->hBtmBlank, BLK->DigitWidth * 2 * 10, 0, SRCPAINT);
    }
}



//-----------------------------------------------------------------------------
//      Blank ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT CALLBACK BlankWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    LPSTR lpWidth, lpHeight, BlkFName;
    CHAR Buff[MAX_PATH];
    BLANK* BLK;    // ����ü �����͸� ���������� �ϸ� ������ �� ���� Ŀ���� ��Ʈ���� ���� �޸��� �ּҸ� �����ϱ� ������ ġ������ ������ �߻��Ѵ�.
                   // ����, ���������� �ƴ� ������ ������ Ŭ������ cbWndExtra ��������� ����ü �����͸� �����س��� ����Ѵ�.

    BLK = (BLANK*)GetWindowLong(hWnd, 0);    // ������ Ŭ������ cbWndExtra ��������� ����Ǿ� �ִ� BLANK* �����͸� �����´�.
    switch (Msg)
    {
    case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
        BLK = (BLANK*)LocalAlloc(LMEM_FIXED, sizeof(BLANK));
        SetWindowLong(hWnd, 0, (LONG)BLK);  // ������ Ŭ������ cbWndExtra ��������� BLANK* �����͸� �����س��´�.

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

    case WM_DESTROY:        //�����찡 �ı�� ��
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

    case WM_PAINT:          //ȭ���� �׷��� �� ������ ������ ��
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
//       Blank ������ ���
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


