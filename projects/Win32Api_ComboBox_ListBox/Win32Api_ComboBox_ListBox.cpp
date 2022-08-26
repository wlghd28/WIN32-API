// Win32Api_ComboBox_ListBox.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_ComboBox_ListBox.h"

#define MAX_LOADSTRING 100


#define NAMEMAX     16      //주민등록상 최대 한글 길이는 6자
#define GROUPMAX    16      //분류명 최대 길이
#define TELNOMAX    20      //082)010-1111-2222


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다. 

static CONST CHAR AppTitle[] = "콤보박스와 리스트박스 활용";
static CONST CHAR MainWindowClassName[] = "MainWnd";
static CONST CHAR DispText[] = "메인 윈도우 입니다.";
static int TextPosX, TextPosY;

// 매크로함수 정의
#define CREATEBUTTON(Title, Style, X,Y, SX, SY, hWnd, ID)       \
    CreateWindow("BUTTON", Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \

#define CREATEEDIT(Title, Style, X,Y, SX, SY, hWnd, ID)         \
    CreateWindowEx(WS_EX_CLIENTEDGE,                            \
                 "EDIT",   Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \

#define CREATESTATIC(Title, Style, X,Y, SX, SY, hWnd, ID)       \
    CreateWindow("STATIC", Title, Style|WS_CHILD|WS_VISIBLE,    \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \


#define CREATECOMBOBOX(Title, Style, X,Y, SX, SY, hWnd, ID)     \
    CreateWindow("COMBOBOX", Title, Style|WS_CHILD|WS_VISIBLE,  \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \

#define CREATELISTBOX(Title, Style, X,Y, SX, SY, hWnd, ID)      \
    CreateWindowEx(WS_EX_CLIENTEDGE,                            \
                 "LISTBOX",  Title, Style|WS_CHILD|WS_VISIBLE,  \
                 X,Y, SX, SY, hWnd, (HMENU)(ID), hInst, NULL)   \



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadString(hInstance, IDS_APP_TITLE, (LPSTR)szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WIN32APICOMBOBOXLISTBOX, (LPSTR)szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APICOMBOBOXLISTBOX));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = MainWndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APICOMBOBOXLISTBOX));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32APICOMBOBOXLISTBOX);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateControl(hWnd);
        break;
    case WM_COMMAND:
            WM_CmdProc(hWnd, message, wParam, lParam);
            return DefWindowProc(hWnd, message, wParam, lParam);      
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}




// 함수 정의

//-----------------------------------------------------------------------------
//      메인 윈도우 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int  I, Sex, Importent;
    CHAR Name[NAMEMAX];
    CHAR Group[GROUPMAX];
    CHAR TelNo[TELNOMAX];
    CHAR Buff[128];
    int wmId = LOWORD(wParam);
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;

    case PhoneBookAddBTID:      //추가버튼
        GetDlgItemText(hWnd, PhoneBookNameEBID, Name, sizeof(Name));
        if (Name[0] == 0)
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
        if (TelNo[0] == 0)
        {
            MessageBox(hWnd, "전화번호를 입력하세요.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hWnd, PhoneBookNumberEBID));
            break;
        }

        GetDlgItemText(hWnd, PhoneBookGroupCBID, Group, sizeof(Group));
        if (Group[0] == 0)
        {
            MessageBox(hWnd, "분류를 선택하세요.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hWnd, PhoneBookGroupCBID));
            break;
        }

        Sex = IsDlgButtonChecked(hWnd, PhoneBookSexRBID);
        Importent = IsDlgButtonChecked(hWnd, PhoneBookImportantCKID);

        wnsprintf(Buff, sizeof(Buff), "%s %s %s %s %s", Group, Name, TelNo,
            Sex != 0 ? "남" : "여", Importent != 0 ? "중요" : "");

        LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
        break;

    case PhoneBookDeleteBTID:   //삭제버튼
        if ((I = LB_GetCurSel(hWnd, PhoneBookViewerLBID)) == LB_ERR)
        {
            MessageBox(hWnd, "삭제할 항목을 선택하세요.", AppTitle, MB_OK);
            break;
        }
        LB_DeleteString(hWnd, PhoneBookViewerLBID, I);
        break;



    default:
        break;
    }

}



//-----------------------------------------------------------------------------
//      컨트롤 생성
//-----------------------------------------------------------------------------
void WINAPI CreateControl(HWND hWnd)
{
    CREATESTATIC("이름", SS_RIGHT, 10, 10, 80, 20, hWnd, -1);
    CREATEEDIT("", ES_AUTOHSCROLL | WS_BORDER, 100, 8, 100, 24, hWnd, PhoneBookNameEBID);
    CREATEBUTTON("남", BS_AUTORADIOBUTTON, 220, 10, 50, 20, hWnd, PhoneBookSexRBID);
    CREATEBUTTON("여", BS_AUTORADIOBUTTON, 280, 10, 50, 20, hWnd, PhoneBookSexRBID + 1);

    CREATESTATIC("전화번호", SS_RIGHT, 10, 40, 80, 20, hWnd, -1);
    CREATEEDIT("", ES_AUTOHSCROLL | WS_BORDER, 100, 38, 100, 24, hWnd, PhoneBookNumberEBID);
    CREATEBUTTON("중요", BS_AUTOCHECKBOX, 220, 40, 50, 20, hWnd, PhoneBookImportantCKID);

    CREATESTATIC("분류", SS_RIGHT, 10, 70, 80, 20, hWnd, -1);
    CREATECOMBOBOX("", CBS_DROPDOWNLIST, 100, 68, 100, 100, hWnd, PhoneBookGroupCBID);
    CREATEBUTTON("추가", 0, 220, 68, 50, 24, hWnd, PhoneBookAddBTID);
    CREATEBUTTON("삭제", 0, 280, 68, 50, 24, hWnd, PhoneBookDeleteBTID);

    CREATELISTBOX("", LBS_SORT | WS_BORDER, 10, 100, 320, 300, hWnd, PhoneBookViewerLBID);

    CB_AddString(hWnd, PhoneBookGroupCBID, "가족");
    CB_AddString(hWnd, PhoneBookGroupCBID, "친구");
    CB_AddString(hWnd, PhoneBookGroupCBID, "동아리");
    CB_AddString(hWnd, PhoneBookGroupCBID, "기타");

}


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
//      이름이 중복되면 TRUE를 리턴함
//-----------------------------------------------------------------------------
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr)
{
    int I, J;
    CHAR Buff[256] = { 0, };

    J = LB_GetCount(hWnd, PhoneBookViewerLBID);
    for (I = 0; I < J; I++)
    {
        SendDlgItemMessage(hWnd, PhoneBookViewerLBID, LB_GETTEXT, I, (LPARAM)Buff);
        if (StrStr(Buff, ToFileStr) != NULL) return TRUE;
    }
    return FALSE;
}



