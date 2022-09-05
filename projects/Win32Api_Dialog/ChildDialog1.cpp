#pragma
#include "framework.h"
#include "ChildDialog1.h"

#define WMCMDID LOWORD(wPrm)

#define NAMEMAX     16      //주민등록상 최대 한글 길이는 6자
#define GROUPMAX    16      //분류명 최대 길이
#define TELNOMAX    20      //082)010-1111-2222

CONST CHAR AppTitle[] = "Win32Api_Dialog_Child1";

// 함수 정의
//-----------------------------------------------------------------------------
//       자식 다이얼로그1 메세지 처리
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
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 0, 70, "이름", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 1, 40, "성별", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 2, 80, "전화번호", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 3, 40, "중요", 0);
    LV_InsertColumn(hDlg, PhoneBookViewerLVID, 4, 60, "분류", 0);

    CB_AddString(hDlg, PhoneBookGroupCBID, "가족");
    CB_AddString(hDlg, PhoneBookGroupCBID, "친구");
    CB_AddString(hDlg, PhoneBookGroupCBID, "동아리");
    CB_AddString(hDlg, PhoneBookGroupCBID, "기타");


    return TRUE;
}

//-----------------------------------------------------------------------------
//      자식 다이얼로그1 WM_COMMAND 메세지 처리
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
    case IDC_BUTTON_CHILD1_ADD:      //추가버튼
        GetDlgItemText(hDlg, PhoneBookNameEBID, Name, sizeof(Name));
        if (Name[0] == 0)
        {
            MessageBox(hDlg, "이름을 입력하세요.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookNameEBID));
            break;
        }

        if (CheckDuplicateName(hDlg, Name))
        {
            MessageBox(hDlg, "이미 같은 이름이 있습니다.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookNameEBID));
            break;
        }

        GetDlgItemText(hDlg, PhoneBookNumberEBID, TelNo, sizeof(TelNo));
        if (TelNo[0] == 0)
        {
            MessageBox(hDlg, "전화번호를 입력하세요.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookNumberEBID));
            break;
        }

        GetDlgItemText(hDlg, PhoneBookGroupCBID, Group, sizeof(Group));
        if (Group[0] == 0)
        {
            MessageBox(hDlg, "분류를 선택하세요.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, PhoneBookGroupCBID));
            break;
        }

        Sex = IsDlgButtonChecked(hDlg, PhoneBookSexRBID);
        Importent = IsDlgButtonChecked(hDlg, PhoneBookImportantCKID);

        wnsprintf(Buff, sizeof(Buff), "%s %s %s %s %s", Group, Name, TelNo,
            Sex != 0 ? "남" : "여", Importent != 0 ? "중요" : "");

        //LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
        Row = LV_GetItemCount(hDlg, PhoneBookViewerLVID);
        LV_InsertItem(hDlg, PhoneBookViewerLVID, Row, Name, 0);
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 1, Sex != 0 ? "남" : "여");
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 2, TelNo);
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 3, Importent != 0 ? "√" : "");
        LV_SetItemText(hDlg, PhoneBookViewerLVID, Row, 4, Group);

        break;

    case IDC_BUTTON_CHILD1_DELETE:   //삭제버튼
        if ((I = LV_GetSelected(hDlg, PhoneBookViewerLVID, -1)) < 0)
        {
            MessageBox(hDlg, "삭제할 항목을 선택하세요.", AppTitle, MB_OK);
            break;
        }
        LV_DeleteItem(hDlg, PhoneBookViewerLVID, I);
        break;

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      자식 다이얼로그1 WM_NOTIFY 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}






//-----------------------------------------------------------------------------
//      스크린 디버그 함수
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
//      이름이 중복되면 TRUE를 리턴함
//-----------------------------------------------------------------------------
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr)
{
    return FALSE;
}




//-----------------------------------------------------------------------------
//      ListView의 컴럼추가
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
//      ListView에서 한줄 추가
//-----------------------------------------------------------------------------
int WINAPI LV_InsertItem(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData)
{
    LV_ITEM LVI;

    ZeroMemory(&LVI, sizeof(LV_ITEM));
    LVI.mask = LVIF_TEXT | LVIF_PARAM;
    LVI.iSubItem = 0;            //안 주면 동작 안함
    LVI.iItem = Row;
    LVI.lParam = ItemData;     //정렬할 때 씀
    LVI.pszText = (LPSTR)DataStr;
    return (int)SendDlgItemMessage(hWnd, LVID, LVM_INSERTITEM, 0, (LPARAM)&LVI);
}



//-----------------------------------------------------------------------------
//      ListView의 Item수를 얻음
//-----------------------------------------------------------------------------
int WINAPI LV_GetItemCount(HWND hWnd, int LVID)
{
    return SendDlgItemMessage(hWnd, LVID, LVM_GETITEMCOUNT, 0, 0);
}



//-----------------------------------------------------------------------------
//      ListView Item Text설정
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
//      ListView의 선택된 Item번호를 얻음 (실패인경우 -1)
//-----------------------------------------------------------------------------
int WINAPI LV_GetSelected(HWND hWnd, int LVID, int StartItemNo)
{
    return (int)SendDlgItemMessage(hWnd, LVID, LVM_GETNEXTITEM, StartItemNo, LVNI_SELECTED);
}



//-----------------------------------------------------------------------------
//      ListView의 주어진 Item을 삭제함
//-----------------------------------------------------------------------------
BOOL WINAPI LV_DeleteItem(HWND hWnd, int LVID, int DelItemNo)
{
    return (BOOL)SendDlgItemMessage(hWnd, LVID, LVM_DELETEITEM, DelItemNo, 0);
}



//-----------------------------------------------------------------------------
//      콤보박스에 항목 추가
//-----------------------------------------------------------------------------
int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr)
{
    return SendDlgItemMessage(hWnd, CBID, CB_ADDSTRING, 0, (LPARAM)ToAddStr);
}



