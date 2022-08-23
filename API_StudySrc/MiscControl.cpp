///////////////////////////////////////////////////////////////////////////////
//                      WIN32 ���� ������ â
//
// ������:
// ���α׷���:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>    //wvnsprintf()
#include <COMMCTRL.H>
#define SCREENDEBUG 1

static CONST CHAR AppTitle[]="WIN32 ���� ������ â ���ø�";
static CONST CHAR MainWindowClassName[]="MainWnd";
static HINSTANCE HInst;



//-----------------------------------------------------------------------------
//      ��� ȭ�� �׸��� ����
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
    {
    RECT R;
    static CONST CHAR DispText[]="���� ������ �Դϴ�.";

    GetClientRect(hWnd, &R);
    DrawText(hDC, DispText, lstrlen(DispText), &R, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }


#define ActionBTID          100
#define IPAddressIPID       101
#define TrackBarTBID        102
#define ProgressBarPBID     103
#define DateTimePickDTPID   104
#define StatusBarSBID       105


//-----------------------------------------------------------------------------
//      ���� ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    int I;
    DWORD IP;
    CHAR Buff[128];
    static int SBParts[]={400, 550, 700};

    switch (Msg)
        {
        case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
            CreateWindow("BUTTON", "�׼�", WS_CHILD|WS_VISIBLE, 10, 10, 100, 24, hWnd, (HMENU)ActionBTID, HInst, NULL);
            CreateWindow(WC_IPADDRESS, "", WS_CHILD|WS_VISIBLE, 10, 44, 200, 24, hWnd, (HMENU)IPAddressIPID, HInst, NULL);
            CreateWindow(TRACKBAR_CLASS, "", TBS_BOTTOM|WS_CHILD|WS_VISIBLE, 10, 78, 200, 32, hWnd, (HMENU)TrackBarTBID, HInst, NULL);

            SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETRANGE, FALSE, MAKELONG(0,10));
            SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETTIC, 0, 2);
            SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETTIC, 0, 5);
            SendDlgItemMessage(hWnd, TrackBarTBID, TBM_SETTIC, 0, 7);

            CreateWindow(PROGRESS_CLASS, "", PBS_MARQUEE|WS_CHILD|WS_VISIBLE, 10, 120, 200, 22, hWnd, (HMENU)ProgressBarPBID, HInst, NULL);
            SendDlgItemMessage(hWnd, ProgressBarPBID, PBM_SETRANGE, 0, MAKELONG(0,100));
            SendDlgItemMessage(hWnd, ProgressBarPBID, PBM_SETPOS, 70, 0);

            CreateWindow(DATETIMEPICK_CLASS, "", WS_CHILD|WS_VISIBLE, 10, 152, 200, 22, hWnd, (HMENU)DateTimePickDTPID, HInst, NULL);

            CreateWindow(STATUSCLASSNAME, "", WS_CHILD|WS_VISIBLE, 10, 184, 200, 22, hWnd, (HMENU)StatusBarSBID, HInst, NULL);
            SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETPARTS, 3, (LPARAM)SBParts);
            SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETTEXT, 0, (LPARAM)"��Ÿ ��Ʈ�� ���Ǹ� ��ĥ�ð��� �Ǿ����ϴ�");
            SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETTEXT, 1, (LPARAM)"�ι�°");
            SendDlgItemMessage(hWnd, StatusBarSBID, SB_SETTEXT, 2, (LPARAM)"����°");


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
            switch (LOWORD(wPrm))
                {
                case ActionBTID:
                    SendDlgItemMessage(hWnd, IPAddressIPID, IPM_GETADDRESS, 0, (LPARAM)&IP);
                    wsprintf(Buff, "IP = %d.%d.%d.%d", IP>>24, (IP>>16)&0xFF, (IP>>8)&0xFF, IP&0xFF);

                    I=SendDlgItemMessage(hWnd, TrackBarTBID, TBM_GETPOS, 0, 0);
                    wsprintf(Buff+lstrlen(Buff), "\r\nTrack Pos = %d", I);

                    MessageBox(hWnd, Buff, AppTitle, MB_OK);
                }
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

    HInst=hInst;

    INITCOMMONCONTROLSEX ICC;
    ICC.dwSize=sizeof(INITCOMMONCONTROLSEX);
    ICC.dwICC=ICC_WIN95_CLASSES|ICC_DATE_CLASSES|ICC_STANDARD_CLASSES|ICC_INTERNET_CLASSES;          //"SysDateTimePick32" �̰��� ����ϱ� ����
    InitCommonControlsEx(&ICC);

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




#ifdef NODEFAULTLIB
//-----------------------------------------------------------------------------
//      VC�� ������ ���� �� �������Ͽ��� ���� ���� ȣ��Ǵ� �Լ�
//      ��ũ �ɼǿ��� /NODEFAULTLIB �� �־�� ȣ���
//-----------------------------------------------------------------------------
int WinMainCRTStartup()
    {
    int Rslt;
    STARTUPINFO SI;

    SI.dwFlags=0;
    GetStartupInfo(&SI);
    Rslt=WinMain(GetModuleHandle(NULL), 0, (LPSTR)NextWord(GetCommandLine(), 1),
        SI.dwFlags & STARTF_USESHOWWINDOW ? SI.wShowWindow:SW_SHOWDEFAULT);

    ExitProcess(Rslt);
    return Rslt;
    }
#endif

