///////////////////////////////////////////////////////////////////////////////
//                  API���� - Ŀ���� ��Ʈ�� - Ź��ð�
//
// ������:
// ���α׷���:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>    //wvnsprintf()
#define SCREENDEBUG 1
#include <stdio.h>

static CONST CHAR AppTitle[]="WIN32 GUI - Ź��ð�";
static CONST CHAR MainWindowClassName[]="MainWnd";





//-----------------------------------------------------------------------------
//          ��Ʈ�� ������ �ε���
//-----------------------------------------------------------------------------
HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName)
    {
    return (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }



//-----------------------------------------------------------------------------
//       hBitmap�� �׸�
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
//      ��� ȭ�� �׸��� ����
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
    {
    HPEN hPenOld;
    HBRUSH hBrOld;
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
        DrawBitmap(hDC, 10, 80, 140, 187, hBtm, 140*2, 187, SRCAND);
        DrawBitmap(hDC, 10, 80, 140, 187, hBtm, 140*2, 0, SRCPAINT);

        DrawBitmap(hDC, 150, 80, 140, 187, hBtm, 140*3, 187, SRCAND);
        DrawBitmap(hDC, 150, 80, 140, 187, hBtm, 140*3, 0, SRCPAINT);

        DrawBitmap(hDC, 290, 80, 70, 187, hBtm, 140*10+0, 187, SRCAND);
        DrawBitmap(hDC, 290, 80, 70, 187, hBtm, 140*10+0, 0, SRCPAINT);

        DrawBitmap(hDC, 360, 80, 140, 187, hBtm, 140*5, 187, SRCAND);
        DrawBitmap(hDC, 360, 80, 140, 187, hBtm, 140*5, 0, SRCPAINT);

        DrawBitmap(hDC, 500, 80, 140, 187, hBtm, 140*9, 187, SRCAND);
        DrawBitmap(hDC, 500, 80, 140, 187, hBtm, 140*9, 0, SRCPAINT);

        DeleteObject(hBtm);
        }
    }



//-----------------------------------------------------------------------------
//      ���� ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //printf("Msg=%X\n", Msg);

    switch (Msg)
        {
        case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
            Ret0:
            return 0;

        case WM_DESTROY:        //�����찡 �ı�� ��
            PostQuitMessage(0); //GetMessage()�� ������ FALSE�� ����� �����ϰ� ��
            goto Ret0;

        case WM_PAINT:          //ȭ���� �׷��� �� ������ ������ ��
            {
            PAINTSTRUCT PS;

            BeginPaint(hWnd, &PS);
            DrawAll(hWnd, PS.hdc);
            EndPaint(hWnd, &PS);
            goto Ret0;
            }

        case WM_SIZE:           //������ ũ���� ��ȭ�� ������ ��
                                //LOWORD(lPrm): Client Width, HIWORD(lPrm): Client Height
            goto Ret0;

        case WM_COMMAND:        //�޴��� Ŭ������ ��
            goto Ret0;

        case WM_KEYDOWN:        //Ű�� ������ ��
            goto Ret0;
        }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
    }




//-----------------------------------------------------------------------------
//      ������ ���ø����̼� ����
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


