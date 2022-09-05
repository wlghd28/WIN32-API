#pragma
#include "framework.h"
#include "ChildDialog1.h"

#define WMCMDID LOWORD(wPrm)

#define NAMEMAX     16      //�ֹε�ϻ� �ִ� �ѱ� ���̴� 6��
#define GROUPMAX    16      //�з��� �ִ� ����
#define TELNOMAX    20      //082)010-1111-2222

CONST CHAR AppTitle[] = "Win32Api_Dialog_Child1";

// �Լ� ����
//-----------------------------------------------------------------------------
//       �ڽ� ���̾�α�1 �޼��� ó��
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ChildDialog1_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitChildDialog1(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_ChildDialog1(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_ChildDialog1(hDlg, message, wParam, lParam);
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR WINAPI InitChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect_Client;
    GetClientRect(GetParent(hDlg), &rect_Client);
    MoveWindow(hDlg, 0, 50, rect_Client.right - rect_Client.left, rect_Client.bottom - rect_Client.top, TRUE);
    ShowWindow(hDlg, SW_SHOW);


    SendDlgItemMessage(hDlg, PhoneBookViewerLVID, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 0, 70, "�̸�", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 1, 40, "����", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 2, 80, "��ȭ��ȣ", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 3, 40, "�߿�", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 4, 60, "�з�", 0);

    CB_AddString(hDlg, PhoneBookGroupCBID, "����");
    CB_AddString(hDlg, PhoneBookGroupCBID, "ģ��");
    CB_AddString(hDlg, PhoneBookGroupCBID, "���Ƹ�");
    CB_AddString(hDlg, PhoneBookGroupCBID, "��Ÿ");


    return TRUE;
}

//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�1 WM_COMMAND �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);

    int  I, Row, Sex, Importent;
    CHAR Name[NAMEMAX];
    CHAR Group[GROUPMAX];
    CHAR TelNo[TELNOMAX];
    CHAR Buff[128];

    switch (wprm)
    {
    case IDC_BUTTON_CHILD1_ADD:      //�߰���ư
        GetDlgItemText(hDlg, PhoneBookNameEBID, Name, sizeof(Name));
        if (Name[0] == 0)
        {
            MessageBox(hDlg, "�̸��� �Է��ϼ���.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookNameEBID));
            break;
        }

        if (CheckDuplicateName(hDlg, Name))
        {
            MessageBox(hDlg, "�̹� ���� �̸��� �ֽ��ϴ�.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookNameEBID));
            break;
        }

        GetDlgItemText(hDlg, PhoneBookNumberEBID, TelNo, sizeof(TelNo));
        if (TelNo[0] == 0)
        {
            MessageBox(hDlg, "��ȭ��ȣ�� �Է��ϼ���.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookNumberEBID));
            break;
        }

        GetDlgItemText(hDlg, PhoneBookGroupCBID, Group, sizeof(Group));
        if (Group[0] == 0)
        {
            MessageBox(hDlg, "�з��� �����ϼ���.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookGroupCBID));
            break;
        }

        Sex = IsDlgButtonChecked(hDlg, PhoneBookSexRBID);
        Importent = IsDlgButtonChecked(hDlg, PhoneBookImportantCKID);

        wnsprintf(Buff, sizeof(Buff), "%s %s %s %s %s", Group, Name, TelNo,
            Sex != 0 ? "��" : "��", Importent != 0 ? "�߿�" : "");

        //LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
        Row = LV_GetItemCount(hDlg, PhoneBookViewerLVID);
        LV_InsertItem(hDlg, PhoneBookViewerLVID, Row, Name, 0);
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 1, Sex != 0 ? "��" : "��");
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 2, TelNo);
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 3, Importent != 0 ? "��" : "");
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 4, Group);

        break;

    case IDC_BUTTON_CHILD1_DELETE:   //������ư
        if ((I = LV_GetSelected(hDlg, PhoneBookViewerLVID, -1)) < 0)
        {
            MessageBox(hDlg, "������ �׸��� �����ϼ���.", AppTitle, MB_OK);
            break;
        }
        LV_DeleteItem(hDlg, PhoneBookViewerLVID, I);
        break;

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�1 WM_NOTIFY �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}






//-----------------------------------------------------------------------------
//      ��ũ�� ����� �Լ�
//-----------------------------------------------------------------------------
VOID Printf_Child1(LPCSTR FormStr, ...)
{
    HDC  hDC;
    char szTmp[MAX_PATH];
    static int  DebugPosY = 0;

    hDC = GetDC(NULL);
    wvsprintf(szTmp, FormStr, (LPSTR)(&FormStr + 1));
    //VsprintfN(szTmp, sizeof(szTmp), FormStr, &FormStr+1);
    TextOut(hDC, 0, DebugPosY, szTmp, lstrlen(szTmp));
    ReleaseDC(NULL, hDC);

    //DebugFile("%s\r\n",szTmp);
    //OutputDebugString(szTmp);

    DebugPosY += 16;
    if (DebugPosY >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;
}



//-----------------------------------------------------------------------------
//      �̸��� �ߺ��Ǹ� TRUE�� ������
//-----------------------------------------------------------------------------
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr)
{
    return FALSE;
}




//-----------------------------------------------------------------------------
//      ListView�� �ķ��߰�
//      Align= LVCFMT_LEFT/LVCFMT_CENTER/LVCFMT_RIGHT
//-----------------------------------------------------------------------------
VOID WINAPI LV_InsertColumn(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align)
{
    LV_COLUMN  LVC;

    LVC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    LVC.fmt = Align;
    LVC.cx = Width;
    LVC.pszText = (LPSTR)ColumnName;
    SendDlgItemMessage(hWnd, LVID, LVM_INSERTCOLUMN, Column, (LPARAM)&LVC);
}



//-----------------------------------------------------------------------------
//      ListView���� ���� �߰�
//-----------------------------------------------------------------------------
int WINAPI LV_InsertItem(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData)
{
    LV_ITEM LVI;

    ZeroMemory(&LVI, sizeof(LV_ITEM));
    LVI.mask = LVIF_TEXT | LVIF_PARAM;
    LVI.iSubItem = 0;            //�� �ָ� ���� ����
    LVI.iItem = Row;
    LVI.lParam = ItemData;     //������ �� ��
    LVI.pszText = (LPSTR)DataStr;
    return (int)SendDlgItemMessage(hWnd, LVID, LVM_INSERTITEM, 0, (LPARAM)&LVI);
}



//-----------------------------------------------------------------------------
//      ListView�� Item���� ����
//-----------------------------------------------------------------------------
int WINAPI LV_GetItemCount(HWND hWnd, int LVID)
{
    return SendDlgItemMessage(hWnd, LVID, LVM_GETITEMCOUNT, 0, 0);
}



//-----------------------------------------------------------------------------
//      ListView Item Text����
//-----------------------------------------------------------------------------
VOID WINAPI LV_SetItemText(HWND hWnd, int LVID, int Row, int Column, LPCSTR DataStr)
{
    LV_ITEM LVI;

    ZeroMemory(&LVI, sizeof(LV_ITEM));
    LVI.mask = LVIF_TEXT;
    LVI.iSubItem = Column;
    LVI.pszText = (LPSTR)DataStr;
    SendDlgItemMessage(hWnd, LVID, LVM_SETITEMTEXT, Row, (LPARAM)&LVI);
}



//-----------------------------------------------------------------------------
//      ListView�� ���õ� Item��ȣ�� ���� (�����ΰ�� -1)
//-----------------------------------------------------------------------------
int WINAPI LV_GetSelected(HWND hWnd, int LVID, int StartItemNo)
{
    return (int)SendDlgItemMessage(hWnd, LVID, LVM_GETNEXTITEM, StartItemNo, LVNI_SELECTED);
}



//-----------------------------------------------------------------------------
//      ListView�� �־��� Item�� ������
//-----------------------------------------------------------------------------
BOOL WINAPI LV_DeleteItem(HWND hWnd, int LVID, int DelItemNo)
{
    return (BOOL)SendDlgItemMessage(hWnd, LVID, LVM_DELETEITEM, DelItemNo, 0);
}



//-----------------------------------------------------------------------------
//      �޺��ڽ��� �׸� �߰�
//-----------------------------------------------------------------------------
int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr)
{
    return SendDlgItemMessage(hWnd, CBID, CB_ADDSTRING, 0, (LPARAM)ToAddStr);
}



