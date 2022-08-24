/*
    ������Ʈ �Ӽ��� ��ũ �ɼ� �׸� ���� ���α׷��� ����� �� ȣ��Ǵ� ù �������� �޶���.
    /SUBSYSTEM:CONSOLE => mainCRTStartup / wmainCRTStartup => main / wmain
    /SUBSYSTEM:WINDOWS => WinMainCRTStartup / wWinMainCRTStartup => WinMain / wWinMain
    /DLL => _DllMainCRTStartup => DllMain

    �� ������Ʈ�� ������Ʈ�� ���� ���� �� WINAPI �Լ��� �� �� ��������� ���� ���״µ��� LNK2019 ������ ���ٸ�
    Visual Studio�� �ֽ� ǥ�� ���̺귯�� ���濡 ���� �߰��ؾ� �� ���̺귯������ �߰��Ʊ� �����̴�.
    ���� msvcrt.lib, ucrt.lib, vcruntime.lib 3���� ���̺귯���� �߰� ���Ӽ��� �߰� ������� �Ѵ�.
*/

//// Win32Api_Base.cpp
#include "Win32Api_Base.h"

// ��������
static CONST CHAR AppTitle[] = "WIN32 ���� ������ â ���ø�";
static CONST CHAR MainWindowClassName[] = "MainWnd";

static CONST CHAR DispText[] = "���� ������ �Դϴ�.";
static int TextPosX, TextPosY;

//--------------------------------------------------------------------------------------
//  ������ ���ø����̼� ����
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    //wc.cbClsExtra = 0;
    //wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //wc.lpszMenuName = MAKEINTRESOURCE(MainMenuID);
    wc.lpszClassName = MainWindowClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wc);

    hWnd = CreateWindow
    (
        MainWindowClassName,
        AppTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        (HMENU)NULL,
        hInst,
        NULL
    );

    ShowWindow(hWnd, CmdShow);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


//--------------------------------------------------------------------------------------
//  VC�� ������ ���� �� �������Ͽ��� ���� ���� ȣ��Ǵ� �Լ�.

//  ������Ʈ �Ӽ��� ��ũ �ɼǿ��� /NODEFAULTLIB �� �־�� ȣ���.

//  C-Runtime ���̺귯���� ����ġ ������ ������ �� ��� 
//  ������Ʈ �Ӽ����� �̵��Ͽ� ���� �Ӽ� > C/C++ > ��� �ɼ� > �⺻ ��Ÿ�� �˻� �ɼ��� '�⺻��'���� �����Ѵ�.

//  __security_init_cookie �Լ�ȣ��� ���� ���� ���� ��Ű /GS(���� ���� �˻�) ������ �� ��� 
//  ������Ʈ �Ӽ����� �̵��Ͽ� ���� �Ӽ� > C/C++ > ��� �ɼ� > ���Ȱ˻� �ɼ��� '������'���� �����Ѵ�.
//--------------------------------------------------------------------------------------
int WinMainCRTStartup(void)
{
    int iRet;
    STARTUPINFO SI;
    SI.dwFlags = 0;
    GetStartupInfo(&SI);
    iRet = WinMain
    (
        GetModuleHandle(0),
        0,
        GetCommandLine(),
        SI.dwFlags & STARTF_USESHOWWINDOW ? SI.wShowWindow : SW_SHOWDEFAULT
    );

    ExitProcess(iRet);

    return iRet;
}


//--------------------------------------------------------------------------------------
//  ��ũ�� ����� �Լ�
//--------------------------------------------------------------------------------------
void Printf(LPCSTR FormStr, ...)  // ��ũ�� ����� �Լ� (��������)
{
    HDC hDC;
    va_list VL;
    CHAR Buff[MAX_PATH];
    static int DebugPosY = 0;

    va_start(VL, FormStr);
    StringCbPrintf(Buff, sizeof(Buff), FormStr, VL);
    va_end(VL);

    hDC = GetDC(NULL);
    TextOut(hDC, 0, DebugPosY, Buff, lstrlen(Buff));
    if ((DebugPosY += 16) >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;

    //OutputDebugString(Buff);
}

//--------------------------------------------------------------------------------------
//  ������ �޽��� ó�� �Լ�
//--------------------------------------------------------------------------------------
static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_CREATE:         // �����찡 ������ �� �ѹ� ��
        break;

    case WM_DESTROY:        //�����찡 �ı�� ��
        PostQuitMessage(0); //GetMessage()�� ������ FALSE�� ����� �����ϰ� ��
        break;

    case WM_PAINT:          //ȭ���� �׷��� �� ������ ������ ��
    {
        PAINTSTRUCT PS;
        BeginPaint(hWnd, &PS);
        DrawAll(hWnd, PS.hdc);
        EndPaint(hWnd, &PS);
    }
        break;

    case WM_LBUTTONDOWN:
        DragStart(hWnd, lPrm);
        break;

    case WM_LBUTTONUP:
        DragFinish(hWnd, lPrm);
        break;

    case WM_MOUSEMOVE:
        DragMoving(hWnd, lPrm);
        break;



    case WM_SIZE:
        break;

    case WM_COMMAND:
        //WM_Proc(wPrm, lPrm);
        break;

    case WM_KEYDOWN:
        break;
    }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
}


//-----------------------------------------------------------------------------
//      ��� ȭ�� �׸��� ����
//-----------------------------------------------------------------------------
static void WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    TextOut(hDC, TextPosX, TextPosY, DispText, lstrlen(DispText));
}


static void WINAPI DrawDrag(HWND hWnd, COLORREF Col)
{
    HDC hDC;

    hDC = GetDC(hWnd);
    SetTextColor(hDC, Col);
    DrawAll(hWnd, hDC);
    ReleaseDC(hWnd, hDC);
}




//-----------------------------------------------------------------------------
//      �巡�� ���� (WM_LBUTTONDOWN)
//-----------------------------------------------------------------------------
void WINAPI DragStart(HWND hWnd, LPARAM lPrm)
{
    HDC hDC;
    SIZE S;
    RECT R;
    POINT P;

    hDC = GetDC(hWnd);
    GetTextExtentPoint(hDC, DispText, lstrlen(DispText), &S);
    ReleaseDC(hWnd, hDC);

    P.x = LOWORD(lPrm);
    P.y = HIWORD(lPrm);

    SetRect(&R, TextPosX, TextPosY, TextPosX + S.cx, TextPosY + S.cy);
    if (PtInRect(&R, P) != FALSE)
    {
        SetCapture(hWnd);
    }
}



//-----------------------------------------------------------------------------
//      �巡�� ���� (WM_LBUTTONUP)
//-----------------------------------------------------------------------------
void WINAPI DragFinish(HWND hWnd, LPARAM lPrm)
{
    if (GetCapture() == hWnd)
    {
        DrawDrag(hWnd, RGB(255, 255, 255));
        TextPosX = LOWORD(lPrm);
        TextPosY = HIWORD(lPrm);
        DrawDrag(hWnd, RGB(0, 0, 0));

        ReleaseCapture();
    }
}



//-----------------------------------------------------------------------------
//      �巡�� �̵� (WM_MOUSEMOVE)
//-----------------------------------------------------------------------------
void WINAPI DragMoving(HWND hWnd, LPARAM lPrm)
{
    if (GetCapture() == hWnd)
    {
        DrawDrag(hWnd, RGB(255, 255, 255));
        TextPosX = LOWORD(lPrm);
        TextPosY = HIWORD(lPrm);
        DrawDrag(hWnd, RGB(255, 0, 0));
    }
}



