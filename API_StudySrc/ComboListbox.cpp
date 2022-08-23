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
#include <stdio.h>


static HINSTANCE HInst;
static CONST CHAR AppTitle[]="�޺��ڽ��� ����Ʈ�ڽ� Ȱ��";
static CONST CHAR MainWindowClassName[]="MainWnd";
static CONST CHAR DispText[]="���� ������ �Դϴ�.";
static int TextPosX, TextPosY;




#define CREATEBUTTON(Title, Style, X,Y, SX, SY, hWnd, ID)       \
    CreateWindow("BUTTON", Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), HInst, NULL)   \

#define CREATEEDIT(Title, Style, X,Y, SX, SY, hWnd, ID)         \
    CreateWindowEx(WS_EX_CLIENTEDGE,                            \
                 "EDIT",   Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), HInst, NULL)   \

#define CREATESTATIC(Title, Style, X,Y, SX, SY, hWnd, ID)       \
    CreateWindow("STATIC", Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), HInst, NULL)   \


#define CREATECOMBOBOX(Title, Style, X,Y, SX, SY, hWnd, ID)     \
    CreateWindow("COMBOBOX", Title, Style|WS_CHILD|WS_VISIBLE,  \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), HInst, NULL)   \

#define CREATELISTBOX(Title, Style, X,Y, SX, SY, hWnd, ID)      \
    CreateWindowEx(WS_EX_CLIENTEDGE,                            \
                 "LISTBOX",  Title, Style|WS_CHILD|WS_VISIBLE,  \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), HInst, NULL)   \


//-----------------------------------------------------------------------------
//      �޺��ڽ��� �׸� �߰�
//-----------------------------------------------------------------------------
int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr)
    {
    return SendDlgItemMessage(hWnd, CBID, CB_ADDSTRING, 0, (LPARAM)ToAddStr);
    }



//-----------------------------------------------------------------------------
//      ����Ʈ�ڽ��� �׸� �߰�
//-----------------------------------------------------------------------------
int WINAPI LB_AddString(HWND hWnd, int LBID, LPCSTR ToAddStr)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_ADDSTRING, 0, (LPARAM)ToAddStr);
    }



//-----------------------------------------------------------------------------
//      ����Ʈ�ڽ����� ���� ���õ� �׸��� ���ؽ��� ����
//-----------------------------------------------------------------------------
int WINAPI LB_GetCurSel(HWND hWnd, int LBID)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_GETCURSEL, 0, 0);
    }



//-----------------------------------------------------------------------------
//      ����Ʈ�ڽ� �׸� ����
//-----------------------------------------------------------------------------
int WINAPI LB_DeleteString(HWND hWnd, int LBID, int ToDelIdx)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_DELETESTRING, ToDelIdx, 0);
    }



//-----------------------------------------------------------------------------
//      ����Ʈ�ڽ� �׸���� ����
//-----------------------------------------------------------------------------
int WINAPI LB_GetCount(HWND hWnd, int LBID)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_GETCOUNT, 0, 0);
    }








#define PhoneBookNameEBID       100
#define PhoneBookSexRBID        101 //(2)
#define PhoneBookNumberEBID     103
#define PhoneBookImportantCKID  104
#define PhoneBookGroupCBID      105
#define PhoneBookAddBTID        106
#define PhoneBookDeleteBTID     107
#define PhoneBookViewerLBID     108



#define NAMEMAX     16      //�ֹε�ϻ� �ִ� �ѱ� ���̴� 6��
#define GROUPMAX    16      //�з��� �ִ� ����
#define TELNOMAX    20      //082)010-1111-2222



//-----------------------------------------------------------------------------
//      �̸��� �ߺ��Ǹ� TRUE�� ������
//-----------------------------------------------------------------------------
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr)
    {
    int I,J;
    CHAR Buff[256];

    J=LB_GetCount(hWnd, PhoneBookViewerLBID);
    for (I=0; I<J; I++)
        {
        SendDlgItemMessage(hWnd, PhoneBookViewerLBID, LB_GETTEXT, I, (LPARAM)Buff);
        if (StrStr(Buff, ToFileStr)!=NULL) return TRUE;
        }
    return FALSE;
    }




//-----------------------------------------------------------------------------
//      ���� ������ WM_COMMAND �޼��� ó��
//-----------------------------------------------------------------------------
VOID WINAPI WM_CmdProc(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
    {
    int  I, Sex, Importent;
    CHAR Name[NAMEMAX];
    CHAR Group[GROUPMAX];
    CHAR TelNo[TELNOMAX];
    CHAR Buff[128];

    switch (LOWORD(wPrm))
        {
        case PhoneBookAddBTID:      //�߰���ư
            GetDlgItemText(hWnd, PhoneBookNameEBID, Name, sizeof(Name));
            if (Name[0]==0)
                {
                MessageBox(hWnd, "�̸��� �Է��ϼ���.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookNameEBID));
                break;
                }

            if (CheckDuplicateName(hWnd, Name))
                {
                MessageBox(hWnd, "�̹� ���� �̸��� �ֽ��ϴ�.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookNameEBID));
                break;
                }

            GetDlgItemText(hWnd, PhoneBookNumberEBID, TelNo, sizeof(TelNo));
            if (TelNo[0]==0)
                {
                MessageBox(hWnd, "��ȭ��ȣ�� �Է��ϼ���.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookNumberEBID));
                break;
                }

            GetDlgItemText(hWnd, PhoneBookGroupCBID, Group, sizeof(Group));
            if (Group[0]==0)
                {
                MessageBox(hWnd, "�з��� �����ϼ���.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookGroupCBID));
                break;
                }

            Sex=IsDlgButtonChecked(hWnd, PhoneBookSexRBID);
            Importent=IsDlgButtonChecked(hWnd, PhoneBookImportantCKID);

            wnsprintf(Buff, sizeof(Buff), "%s %s %s %s %s", Group, Name, TelNo,
                Sex!=0 ? "��":"��", Importent!=0 ? "�߿�":"");

            LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
            break;

        case PhoneBookDeleteBTID:   //������ư
            if ((I=LB_GetCurSel(hWnd, PhoneBookViewerLBID))==LB_ERR)
                {
                MessageBox(hWnd, "������ �׸��� �����ϼ���.", AppTitle, MB_OK);
                break;
                }
            LB_DeleteString(hWnd, PhoneBookViewerLBID, I);
            break;
        }
    }



//-----------------------------------------------------------------------------
//      ���� ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    switch (Msg)
        {
        case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
            CREATESTATIC("�̸�", SS_RIGHT,            10, 10,  80, 20, hWnd, -1);
            CREATEEDIT("", ES_AUTOHSCROLL|WS_BORDER, 100,  8, 100, 24, hWnd, PhoneBookNameEBID);
            CREATEBUTTON("��", BS_AUTORADIOBUTTON,   220, 10,  50, 20, hWnd, PhoneBookSexRBID);
            CREATEBUTTON("��", BS_AUTORADIOBUTTON,   280, 10,  50, 20, hWnd, PhoneBookSexRBID+1);

            CREATESTATIC("��ȭ��ȣ", SS_RIGHT,        10, 40,  80, 20, hWnd, -1);
            CREATEEDIT("", ES_AUTOHSCROLL|WS_BORDER, 100, 38, 100, 24, hWnd, PhoneBookNumberEBID);
            CREATEBUTTON("�߿�", BS_AUTOCHECKBOX,    220, 40,  50, 20, hWnd, PhoneBookImportantCKID);

            CREATESTATIC("�з�", SS_RIGHT,            10, 70,  80, 20, hWnd, -1);
            CREATECOMBOBOX("", CBS_DROPDOWNLIST,     100, 68, 100,100, hWnd, PhoneBookGroupCBID);
            CREATEBUTTON("�߰�", 0,                  220, 68,  50, 24, hWnd, PhoneBookAddBTID);
            CREATEBUTTON("����", 0,                  280, 68,  50, 24, hWnd, PhoneBookDeleteBTID);

            CREATELISTBOX("", LBS_SORT|WS_BORDER,     10,100, 320,300, hWnd, PhoneBookViewerLBID);

            CB_AddString(hWnd, PhoneBookGroupCBID, "����");
            CB_AddString(hWnd, PhoneBookGroupCBID, "ģ��");
            CB_AddString(hWnd, PhoneBookGroupCBID, "���Ƹ�");
            CB_AddString(hWnd, PhoneBookGroupCBID, "��Ÿ");

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
                      CW_USEDEFAULT, CW_USEDEFAULT, 348, 428,
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



//-----------------------------------------------------------------------------
//      �ܼ� ��Ǯ ����
//-----------------------------------------------------------------------------
int main()
    {
    return WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOW);
    }


