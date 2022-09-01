// Win32Api_TreeView.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32Api_TreeView.h"

#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
CHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
CHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
int _iWindow_Width = 800;
int _iWindow_Height = 600;

static CONST CHAR AppTitle[] = "WIN32 메인 윈도우 창 템플릿";
static CONST CHAR MainWindowClassName[] = "MainWnd";
HTREEITEM hTr1, hTr2;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WIN32APITREEVIEW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APITREEVIEW));

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
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = MainWndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APITREEVIEW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WIN32APITREEVIEW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
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

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, _iWindow_Width, _iWindow_Height, nullptr, nullptr, hInstance, nullptr);

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
    //HTREEITEM hTr1, hTr2;

    switch (message)
    {
    case WM_CREATE:
        CreateControl(hWnd);
        InitTreeView(hWnd);
        break;
    case WM_COMMAND:
        WM_CmdProc(hWnd, message, wParam, lParam);
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_NOTIFY:
        WM_NotifyProc(hWnd, message, wParam, lParam);
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawAll(hWnd, ps.hdc);
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




//-----------------------------------------------------------------------------
//      메인 윈도우 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

    case DeleteItemBtnID:
        if ((hTr1 = TV_GetCurSel(hWnd, TreeViewID)) == NULL)
        {
            MessageBox(hWnd, "지울 항목을 선택하세요", AppTitle, MB_OK);
            break;
        }
        TV_DeleteItem(hWnd, TreeViewID, hTr1);
        break;

    default:
        break;
    }

}

//-----------------------------------------------------------------------------
//      메인 윈도우 WM_NOTIFY 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    NMTREEVIEW* pNmtv = (NMTREEVIEW*)lParam;
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case TreeViewID:
    {
        switch (pNmtv->hdr.code)
        {
        case NM_CLICK:
            break;

        case TVN_ITEMEXPANDED:
            break;

        case TVN_ITEMEXPANDING:
        {
            if (!(pNmtv->itemNew.state & TVIS_EXPANDED))   // 확장
            {
                //printf("확장\n");
                HTREEITEM htrChild;
                char cArr_ItemPath[MAX_PATH] = { 0, };
                char cArr_DrivePath[MAX_PATH] = { 0, };
                char cArr_ApsolPath[MAX_PATH] = { 0, };

                TV_GetItemPath(hWnd, TreeViewID, pNmtv->itemNew.hItem, cArr_ItemPath);

                sprintf(cArr_DrivePath, "%s", "C:");
                sprintf(cArr_ApsolPath, "%s\\%s\\*.*", cArr_DrivePath, cArr_ItemPath);
                //printf("%s\n", cArr_ApsolPath);

                htrChild = TV_GetChildCurSel(hWnd, TreeViewID, pNmtv->itemNew.hItem);
                if (htrChild)   TV_DeleteItem(hWnd,TreeViewID, htrChild);

                FileList(hWnd, pNmtv->itemNew.hItem, cArr_ApsolPath);
            }
            else  // 축소
            {
                //printf("축소\n");
                TV_DeleteAllChildItem(hWnd, TreeViewID, pNmtv->itemNew.hItem);
            }
        }
            break;
         
        default:
            break;
        }
    }
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
    CreateWindow(/*WC_TREEVIEW*/"SysTreeView32", "", TVS_SHOWSELALWAYS | TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS | WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 10, _iWindow_Width - 30 - 100, _iWindow_Height - 80,
        (HWND)hWnd, (HMENU)TreeViewID, hInst, NULL);

    //CreateWindow("BUTTON", "삭제", WS_CHILD | WS_VISIBLE,
    //    _iWindow_Width - 30 - 100 + 20, 10, 80, 40,
    //    (HWND)hWnd, (HMENU)DeleteItemBtnID, hInst, NULL);

}

//-----------------------------------------------------------------------------
//      트리뷰 초기화
//-----------------------------------------------------------------------------
void WINAPI InitTreeView(HWND hWnd)
{
    /*hTr1 = TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인1", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr1, TVI_LAST, "서브1-1", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr1, TVI_LAST, "서브1-1", 0);
    hTr2 = TV_InsertItem(hWnd, TreeViewID, hTr1, TVI_LAST, "서브1-1", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "서브1-1-1", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "서브1-1-2", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "서브1-1-3", 0);

    hTr1 = TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인2", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr1, TVI_LAST, "서브2-1", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr1, TVI_LAST, "서브2-1", 0);
    TV_InsertItem(hWnd, TreeViewID, hTr1, TVI_LAST, "서브2-1", 0);
    TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인3", 0);
    TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인4", 0);*/


    CHAR cArrPath[MAX_PATH];

    //GetWindowsDirectory(cArrPath, MAX_PATH);
    sprintf(cArrPath, "%s", "C:");

    strcat(cArrPath, "\\*.*");

    //printf("%s\n", cArrPath);

    FileList(hWnd, NULL, cArrPath);

}

//-----------------------------------------------------------------------------
//      윈도우 파일리스트 탐색
//-----------------------------------------------------------------------------
void FileList(HWND hWnd, HTREEITEM htr, char* path)
{
    HANDLE hSrch;
    WIN32_FIND_DATA wfd;
    BOOL bResult = TRUE;
    //char drive[_MAX_DRIVE];
    //char dir[MAX_PATH];
    //char newpath[MAX_PATH];
    HTREEITEM htr_before;

    //printf("\n검색 경로 = %s\n", path);

    hSrch = FindFirstFile(path, &wfd);

    if (hSrch == INVALID_HANDLE_VALUE) return;

    //_splitpath(path, drive, dir, NULL, NULL);

    while (bResult) 
    {
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
        {
            //printf("%s\n", wfd.cFileName);

            if (strcmp(wfd.cFileName, ".") && strcmp(wfd.cFileName, "..")) 
            {
                //printf("%s\n", wfd.cFileName);
                htr_before = TV_InsertItem(hWnd, TreeViewID, htr, TVI_LAST, wfd.cFileName, 0);
                TV_InsertItem(hWnd, TreeViewID, htr_before, TVI_LAST, NULL, 0);

                //sprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
                //FileList(hWnd, htr_before, newpath);
            }
        }
        else 
        {
            //printf("%s%s%s\n", drive, dir, wfd.cFileName);
            TV_InsertItem(hWnd, TreeViewID, htr, TVI_LAST, wfd.cFileName, 0);
        }

        bResult = FindNextFile(hSrch, &wfd);
    }

    FindClose(hSrch);
}


//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    RECT R;
    static CONST CHAR DispText[] = "메인 윈도우 입니다.";

    GetClientRect(hWnd, &R);
    DrawText(hDC, DispText, lstrlen(DispText), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}



//-----------------------------------------------------------------------------
//      TreeView에 Item을 삽입합니다
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_InsertItem(HWND hWnd, int TVID, HTREEITEM hParent, HTREEITEM hInsAfter, LPCSTR Str, LPARAM lPrm)
{
    TV_INSERTSTRUCT TVIS;

    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);                           // 핸들을 윈도우 부모핸들에서 TreeControl 핸들로 변경
    TVIS.hParent = hParent;
    TVIS.hInsertAfter = hInsAfter;
    TVIS.item.mask = TVIF_TEXT | TVIF_PARAM;                                //TVIF_SELECTEDIMAGE|TVIF_IMAGE|
    TVIS.item.pszText = (LPSTR)Str;
    TVIS.item.lParam = lPrm;
    //TVIS.item.iImage  =
    //TVIS.item.iSelectedImage=ImageNo;
    return (HTREEITEM)SendMessage(hWnd, TVM_INSERTITEM, 0, (LPARAM)&TVIS);  // SendMessage 쓰는 이유 >> TreeControl 핸들로도 함수를 호출하는 경우도 있기 때문에 범용으로 사용하기 위함
    //return (HTREEITEM)SendDlgItemMessage(hWnd, TVID, TVM_INSERTITEM, 0, (LPARAM)&TVIS);
}



//-----------------------------------------------------------------------------
//      주어진 TV Item을 삭제함
//-----------------------------------------------------------------------------
BOOL WINAPI TV_DeleteItem(HWND hWnd, int TVID, HTREEITEM hItem)
{
    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);
    return (BOOL)SendMessage(hWnd, TVM_DELETEITEM, 0, (LPARAM)hItem);
}

//-----------------------------------------------------------------------------
//      TreeView에서 선택된 항목의 자식 노드를 전부 삭제한다.
//-----------------------------------------------------------------------------
BOOL WINAPI TV_DeleteAllChildItem(HWND hWnd, int TVID, HTREEITEM hItem)
{
    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);
    return (BOOL)PostMessage(hWnd, TVM_EXPAND, TVE_COLLAPSE | TVE_COLLAPSERESET, reinterpret_cast<LPARAM>(hItem));
}

//-----------------------------------------------------------------------------
//      TreeView의 현재선택된 항목을 얻습니다 (실패하면 Null) TreeView_GetSelection()
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_GetCurSel(HWND hWnd, int TVID)
{
    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);
    return (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_CARET, NULL);
}

//-----------------------------------------------------------------------------
//      TreeView의 현재선택된 항목의 부모 항목을 얻습니다 (실패하면 Null) TreeView_GetSelection()
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_GetParentCurSel(HWND hWnd, int TVID, HTREEITEM htr)
{
    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);
    return (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)htr);
}

//-----------------------------------------------------------------------------
//      TreeView의 현재선택된 항목의 첫번째 자식 항목을 얻습니다 (실패하면 Null) TreeView_GetSelection()
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_GetChildCurSel(HWND hWnd, int TVID, HTREEITEM htr)
{
    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);
    return (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)htr);
}


//-----------------------------------------------------------------------------
//      TreeView의 아이템 정보를 얻습니다 (실패하면 Null) TreeView_GetSelection()
//-----------------------------------------------------------------------------
TVITEM WINAPI TV_GetItemInfo(HWND hWnd, int TVID, HTREEITEM htr)
{
    if (TVID != 0) hWnd = GetDlgItem(hWnd, TVID);
    TVITEM item;
    item.hItem = htr;
    item.mask = TVIF_TEXT;
    item.pszText = (LPSTR)LocalAlloc(LMEM_FIXED, sizeof(CHAR) * MAX_PATH);
    item.cchTextMax = MAX_PATH;
    ::SendMessage(hWnd, TVM_GETITEM, 0, (LPARAM)&item);

    return item;
}

//-----------------------------------------------------------------------------
//       TreeView에서 선택된 항목의 절대경로를 구합니다.
//-----------------------------------------------------------------------------
void WINAPI TV_GetItemPath(HWND hWnd, int TVID, HTREEITEM htr, char* path)
{
    if (htr == NULL) return;

    HTREEITEM hItem_Parent = TV_GetParentCurSel(hWnd, TreeViewID, htr);

    TVITEM tvItem_Current = TV_GetItemInfo(hWnd, TreeViewID, htr);

    char tmpPath[MAX_PATH] = { 0, };

    strcpy(tmpPath, path);

    if(strlen(path) == 0)   sprintf(path, "%s", tvItem_Current.pszText);
    else                    sprintf(path, "%s\\%s", tvItem_Current.pszText, tmpPath);

    TV_GetItemPath(hWnd, TVID, hItem_Parent, path);

    LocalFree(tvItem_Current.pszText);
}
