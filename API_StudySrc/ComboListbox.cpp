///////////////////////////////////////////////////////////////////////////////
//                      WIN32 메인 윈도우 창
//
// 시작일:
// 프로그래머:
///////////////////////////////////////////////////////////////////////////////

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>    //wvnsprintf()
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








#define PhoneBookNameEBID       100
#define PhoneBookSexRBID        101 //(2)
#define PhoneBookNumberEBID     103
#define PhoneBookImportantCKID  104
#define PhoneBookGroupCBID      105
#define PhoneBookAddBTID        106
#define PhoneBookDeleteBTID     107
#define PhoneBookViewerLBID     108



#define NAMEMAX     16      //주민등록상 최대 한글 길이는 6자
#define GROUPMAX    16      //분류명 최대 길이
#define TELNOMAX    20      //082)010-1111-2222



//-----------------------------------------------------------------------------
//      이름이 중복되면 TRUE를 리턴함
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
//      메인 윈도우 WM_COMMAND 메세지 처리
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

            LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
            break;

        case PhoneBookDeleteBTID:   //삭제버튼
            if ((I=LB_GetCurSel(hWnd, PhoneBookViewerLBID))==LB_ERR)
                {
                MessageBox(hWnd, "삭제할 항목을 선택하세요.", AppTitle, MB_OK);
                break;
                }
            LB_DeleteString(hWnd, PhoneBookViewerLBID, I);
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
            CREATEEDIT("", ES_AUTOHSCROLL|WS_BORDER, 100,  8, 100, 24, hWnd, PhoneBookNameEBID);
            CREATEBUTTON("남", BS_AUTORADIOBUTTON,   220, 10,  50, 20, hWnd, PhoneBookSexRBID);
            CREATEBUTTON("여", BS_AUTORADIOBUTTON,   280, 10,  50, 20, hWnd, PhoneBookSexRBID+1);

            CREATESTATIC("전화번호", SS_RIGHT,        10, 40,  80, 20, hWnd, -1);
            CREATEEDIT("", ES_AUTOHSCROLL|WS_BORDER, 100, 38, 100, 24, hWnd, PhoneBookNumberEBID);
            CREATEBUTTON("중요", BS_AUTOCHECKBOX,    220, 40,  50, 20, hWnd, PhoneBookImportantCKID);

            CREATESTATIC("분류", SS_RIGHT,            10, 70,  80, 20, hWnd, -1);
            CREATECOMBOBOX("", CBS_DROPDOWNLIST,     100, 68, 100,100, hWnd, PhoneBookGroupCBID);
            CREATEBUTTON("추가", 0,                  220, 68,  50, 24, hWnd, PhoneBookAddBTID);
            CREATEBUTTON("삭제", 0,                  280, 68,  50, 24, hWnd, PhoneBookDeleteBTID);

            CREATELISTBOX("", LBS_SORT|WS_BORDER,     10,100, 320,300, hWnd, PhoneBookViewerLBID);

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


