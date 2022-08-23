///////////////////////////////////////////////////////////////////////////////
//              ��ư ��Ʈ�Ѱ� ����Ʈ ��Ʈ��
//
// ������:
// ���α׷���:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Stdio.h>


static CONST CHAR AppTitle[]="WIN32 ���� ������ â";
static CONST CHAR MainWindowClassName[]="MainWnd";


static CONST CHAR DispText[]="���� ������ �Դϴ�.";
static HINSTANCE HInst;



#define TEST1_BTNID     0
#define TEST2_BTNID     1
#define TEST3_BTNID     2
#define TEST1_EDITID    3



//-----------------------------------------------------------------------------
//      ���� ������ WM_COMMAND �޼��� ó��
//-----------------------------------------------------------------------------
VOID WINAPI WM_CmdProc(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
    {
    CHAR Buff[80];

    switch (wPrm)
        {
        case TEST1_BTNID:
            SetDlgItemInt(hWnd, TEST1_EDITID, IsDlgButtonChecked(hWnd, TEST1_BTNID), FALSE);
            break;

        case TEST2_BTNID:
            GetDlgItemText(hWnd, TEST2_BTNID, Buff, sizeof(Buff));
            SetDlgItemText(hWnd, TEST1_EDITID, Buff);
            break;

        case TEST3_BTNID:
            SetDlgItemText(hWnd, TEST1_EDITID, "3����ư ����");
        }
    }



//-----------------------------------------------------------------------------
//      ���� ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //Printf("Msg=%X", Msg);

    switch (Msg)
        {
        case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
            CreateWindow("BUTTON", "�׽�Ʈ��ư1", BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE,
                              10, 10, 100, 30,
                              hWnd, (HMENU)TEST1_BTNID, HInst, NULL);

            CreateWindow("BUTTON", "�׽�Ʈ��ư2", WS_CHILD|WS_VISIBLE,
                              120, 10, 100, 30,
                              hWnd, (HMENU)TEST2_BTNID, HInst, NULL);

            CreateWindow("BUTTON", "�׽�Ʈ��ư3", WS_CHILD|WS_VISIBLE,
                              230, 10, 100, 30,
                              hWnd, (HMENU)TEST3_BTNID, HInst, NULL);

            CreateWindow("EDIT", "�ȳ�!", ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE,
                              10, 50, 100, 20,
                              hWnd, (HMENU)TEST1_EDITID, HInst, NULL);

            //SendDlgItemMessage(hWnd, TEST1_EDITID, EM_LIMITTEXT, 5, 0);

            Ret0:
            return 0;

        case WM_DESTROY:        //�����찡 �ı�� ��
            PostQuitMessage(0); //GetMessage()�� ������ FALSE�� ����� �����ϰ� ��
            goto Ret0;

        case WM_COMMAND:        //�޴��� Ŭ������ ��
            WM_CmdProc(hWnd, wPrm, lPrm);
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

    HInst=hInst;

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
                      CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
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


//-----------------------------------------------------------------------------
//      �ܼ� ��Ǯ ����
//-----------------------------------------------------------------------------
int main()
    {
    return WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOW);
    }


