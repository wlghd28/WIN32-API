///////////////////////////////////////////////////////////////////////////////
//                      LISTBOX 와 COMBOBOX
//
// 시작일:
// 프로그래머:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>    //wvnsprintf()
#include <CommCtrl.h>   //ListView
#include <stdio.h>


static HINSTANCE HInst;
static CONST CHAR AppTitle[]="콤보박스와 리스트박스 활용";
static CONST CHAR MainWindowClassName[]="MainWnd";
static CONST CHAR DispText[]="메인 윈도우 입니다.";
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


#define CREATELISTVIEW(Title, Style, X,Y, SX, SY, hWnd, ID)         \
    CreateWindowEx(WS_EX_CLIENTEDGE,                                \
                 "SysListView32",  Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), HInst, NULL)       \

//"SysListView32" WC_LISTVIEW


//-----------------------------------------------------------------------------
//      콤보박스에 항목 추가
//-----------------------------------------------------------------------------
int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr)
    {
    return SendDlgItemMessage(hWnd, CBID, CB_ADDSTRING, 0, (LPARAM)ToAddStr);
    }



//-----------------------------------------------------------------------------
//      리스트박스에 항목 추가
//-----------------------------------------------------------------------------
int WINAPI LB_AddString(HWND hWnd, int LBID, LPCSTR ToAddStr)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_ADDSTRING, 0, (LPARAM)ToAddStr);
    }



//-----------------------------------------------------------------------------
//      리스트박스에서 현재 선택된 항목의 인텍스를 리턴
//-----------------------------------------------------------------------------
int WINAPI LB_GetCurSel(HWND hWnd, int LBID)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_GETCURSEL, 0, 0);
    }



//-----------------------------------------------------------------------------
//      리스트박스 항목 삭제
//-----------------------------------------------------------------------------
int WINAPI LB_DeleteString(HWND hWnd, int LBID, int ToDelIdx)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_DELETESTRING, ToDelIdx, 0);
    }



//-----------------------------------------------------------------------------
//      리스트박스 항목수를 리턴
//-----------------------------------------------------------------------------
int WINAPI LB_GetCount(HWND hWnd, int LBID)
    {
    return SendDlgItemMessage(hWnd, LBID, LB_GETCOUNT, 0, 0);
    }



//-----------------------------------------------------------------------------
//      ListView의 컴럼추가
//      Align= LVCFMT_LEFT/LVCFMT_CENTER/LVCFMT_RIGHT
//-----------------------------------------------------------------------------
VOID WINAPI LV_InsertColumn(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align)
    {
    LV_COLUMN  LVC;

    LVC.mask    = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
    LVC.fmt     = Align;
    LVC.cx      = Width;
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
    LVI.mask    = LVIF_TEXT|LVIF_PARAM;
    LVI.iSubItem= 0;            //안 주면 동작 안함
    LVI.iItem   = Row;
    LVI.lParam  = ItemData;     //정렬할 때 씀
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
    LVI.mask    = LVIF_TEXT;
    LVI.iSubItem= Column;
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




#define PhoneBookNameEBID       100
#define PhoneBookSexRBID        101 //(2)
#define PhoneBookNumberEBID     103
#define PhoneBookImportantCKID  104
#define PhoneBookGroupCBID      105
#define PhoneBookAddBTID        106
#define PhoneBookDeleteBTID     107
#define PhoneBookViewerLVID     108




#define NAMEMAX     16      //주민등록상 최대 한글 길이는 6자
#define GROUPMAX    16      //분류명 최대 길이
#define TELNOMAX    20      //082)010-1111-2222



//-----------------------------------------------------------------------------
//      이름이 중복되면 TRUE를 리턴함
//-----------------------------------------------------------------------------
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr)
    {
#if 0
    int I,J;
    CHAR Buff[256];

    J=LB_GetCount(hWnd, PhoneBookViewerLBID);
    for (I=0; I<J; I++)
        {
        SendDlgItemMessage(hWnd, PhoneBookViewerLBID, LB_GETTEXT, I, (LPARAM)Buff);
        if (StrStr(Buff, ToFileStr)!=NULL) return TRUE;
        }
#endif
    return FALSE;
    }




//-----------------------------------------------------------------------------
//      메인 윈도우 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
VOID WINAPI WM_CmdProc(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
    {
    int  I, Row, Sex, Importent;
    CHAR Name[NAMEMAX];
    CHAR Group[GROUPMAX];
    CHAR TelNo[TELNOMAX];
    CHAR Buff[128];

    switch (LOWORD(wPrm))
        {
        case PhoneBookAddBTID:      //추가버튼
            GetDlgItemText(hWnd, PhoneBookNameEBID, Name, sizeof(Name));
            if (Name[0]==0)
                {
                MessageBox(hWnd, "이름을 입력하세요.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookNameEBID));
                break;
                }

            if (CheckDuplicateName(hWnd, Name))
                {
                MessageBox(hWnd, "이미 같은 이름이 있습니다.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookNameEBID));
                break;
                }

            GetDlgItemText(hWnd, PhoneBookNumberEBID, TelNo, sizeof(TelNo));
            if (TelNo[0]==0)
                {
                MessageBox(hWnd, "전화번호를 입력하세요.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookNumberEBID));
                break;
                }

            GetDlgItemText(hWnd, PhoneBookGroupCBID, Group, sizeof(Group));
            if (Group[0]==0)
                {
                MessageBox(hWnd, "분류를 선택하세요.", AppTitle, MB_OK);
                SetFocus(GetDlgItem(hWnd, PhoneBookGroupCBID));
                break;
                }

            Sex=IsDlgButtonChecked(hWnd, PhoneBookSexRBID);
            Importent=IsDlgButtonChecked(hWnd, PhoneBookImportantCKID);

            wnsprintf(Buff, sizeof(Buff), "%s %s %s %s %s", Group, Name, TelNo,
                Sex!=0 ? "남":"여", Importent!=0 ? "중요":"");

            //LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
            Row=LV_GetItemCount(hWnd, PhoneBookViewerLVID);
            LV_InsertItem(hWnd, PhoneBookViewerLVID, Row, Name, 0);
            LV_SetItemText(hWnd, PhoneBookViewerLVID, Row, 1, Sex!=0 ? "남":"여");
            LV_SetItemText(hWnd, PhoneBookViewerLVID, Row, 2, TelNo);
            LV_SetItemText(hWnd, PhoneBookViewerLVID, Row, 3, Importent!=0 ? "√":"");
            LV_SetItemText(hWnd, PhoneBookViewerLVID, Row, 4, Group);

            break;

        case PhoneBookDeleteBTID:   //삭제버튼
            if ((I=LV_GetSelected(hWnd, PhoneBookViewerLVID, -1))<0)
                {
                MessageBox(hWnd, "삭제할 항목을 선택하세요.", AppTitle, MB_OK);
                break;
                }
            LV_DeleteItem(hWnd, PhoneBookViewerLVID, I);
            break;
        }
    }



//-----------------------------------------------------------------------------
//      메인 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    switch (Msg)
        {
        case WM_CREATE:         //윈도우가 생성될 때 한번 옴
            CREATESTATIC("이름", SS_RIGHT,            10, 10,  80, 20, hWnd, -1);
            CREATEEDIT("홍길홍", ES_AUTOHSCROLL|WS_BORDER, 100,  8, 100, 24, hWnd, PhoneBookNameEBID);
            CREATEBUTTON("남", BS_AUTORADIOBUTTON,   220, 10,  50, 20, hWnd, PhoneBookSexRBID);
            CREATEBUTTON("여", BS_AUTORADIOBUTTON,   280, 10,  50, 20, hWnd, PhoneBookSexRBID+1);

            CREATESTATIC("전화번호", SS_RIGHT,        10, 40,  80, 20, hWnd, -1);
            CREATEEDIT("010-1111-2222", ES_AUTOHSCROLL|WS_BORDER, 100, 38, 100, 24, hWnd, PhoneBookNumberEBID);
            CREATEBUTTON("중요", BS_AUTOCHECKBOX,    220, 40,  50, 20, hWnd, PhoneBookImportantCKID);

            CREATESTATIC("분류", SS_RIGHT,            10, 70,  80, 20, hWnd, -1);
            CREATECOMBOBOX("", CBS_DROPDOWNLIST,     100, 68, 100,100, hWnd, PhoneBookGroupCBID);
            CREATEBUTTON("추가", 0,                  220, 68,  50, 24, hWnd, PhoneBookAddBTID);
            CREATEBUTTON("삭제", 0,                  280, 68,  50, 24, hWnd, PhoneBookDeleteBTID);

            CREATELISTVIEW("", LVS_SHOWSELALWAYS|LVS_REPORT|WS_BORDER, 10,100, 320,300, hWnd, PhoneBookViewerLVID);
            //LVS_LIST

            SendDlgItemMessage(hWnd, PhoneBookViewerLVID, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
            LV_InsertColumn(hWnd, PhoneBookViewerLVID, 0, 70, "이름", 0);
            LV_InsertColumn(hWnd, PhoneBookViewerLVID, 1, 40, "성별", 0);
            LV_InsertColumn(hWnd, PhoneBookViewerLVID, 2, 80, "전화번호", 0);
            LV_InsertColumn(hWnd, PhoneBookViewerLVID, 3, 40, "중요", 0);
            LV_InsertColumn(hWnd, PhoneBookViewerLVID, 4, 60, "분류", 0);

            CB_AddString(hWnd, PhoneBookGroupCBID, "가족");
            CB_AddString(hWnd, PhoneBookGroupCBID, "친구");
            CB_AddString(hWnd, PhoneBookGroupCBID, "동아리");
            CB_AddString(hWnd, PhoneBookGroupCBID, "기타");

            Ret0:
            return 0;

        case WM_DESTROY:        //윈도우가 파기될 때
            PostQuitMessage(0); //GetMessage()의 리턴을 FALSE로 만들어 종료하게 함
            goto Ret0;

        case WM_COMMAND:        //메뉴를 클릭했을 때
            WM_CmdProc(hWnd, wPrm, lPrm);
            goto Ret0;
        }

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
    }




//-----------------------------------------------------------------------------
//      윈도우 어플리케이션 메인
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
//      콘솔 어풀 메인
//-----------------------------------------------------------------------------
int main()
    {
    return WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOW);
    }



