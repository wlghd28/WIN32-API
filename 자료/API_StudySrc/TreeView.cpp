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
#include <Commctrl.h>   //TreeView
#define SCREENDEBUG 1

static CONST CHAR AppTitle[]="WIN32 메인 윈도우 창 템플릿";
static CONST CHAR MainWindowClassName[]="MainWnd";

static HINSTANCE HInst;


#define TreeViewID          100
#define DeleteItemBtnID     101



//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
static VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
    {
    RECT R;
    static CONST CHAR DispText[]="메인 윈도우 입니다.";

    GetClientRect(hWnd, &R);
    DrawText(hDC, DispText, lstrlen(DispText), &R, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }



//-----------------------------------------------------------------------------
//      TreeView에 Item을 삽입합니다
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_InsertItem(HWND hWnd, int TVID, HTREEITEM hParent, HTREEITEM hInsAfter, LPCSTR Str, LPARAM lPrm)
    {
    TV_INSERTSTRUCT TVIS;

    if (TVID!=0) hWnd=GetDlgItem(hWnd, TVID);
    TVIS.hParent        = hParent;
    TVIS.hInsertAfter   = hInsAfter;
    TVIS.item.mask      = TVIF_TEXT|TVIF_PARAM;         //TVIF_SELECTEDIMAGE|TVIF_IMAGE|
    TVIS.item.pszText   = (LPSTR)Str;
    TVIS.item.lParam    = lPrm;
    //TVIS.item.iImage  =
    //TVIS.item.iSelectedImage=ImageNo;
    return (HTREEITEM)SendMessage(hWnd, TVM_INSERTITEM, 0, (LPARAM)&TVIS);
    //return (HTREEITEM)SendDlgItemMessage(hWnd, TVID, TVM_INSERTITEM, 0, (LPARAM)&TVIS);
    }



//-----------------------------------------------------------------------------
//      주어진 TV Item을 삭제함
//-----------------------------------------------------------------------------
BOOL WINAPI TV_DeleteItem(HWND hWnd, int TVID, HTREEITEM hItem)
    {
    if (TVID!=0) hWnd=GetDlgItem(hWnd, TVID);
    return (BOOL)SendMessage(hWnd, TVM_DELETEITEM, 0, (LPARAM)hItem);
    }



//-----------------------------------------------------------------------------
//      TreeView의 현재선택된 항목을 얻습니다 (실패하면 Null) TreeView_GetSelection()
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_GetCurSel(HWND hWnd, int TVID)
    {
    if (TVID!=0) hWnd=GetDlgItem(hWnd, TVID);
    return (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_CARET, NULL);
    }



//-----------------------------------------------------------------------------
//      메인 윈도우 메세지 처리
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //Printf("Msg=%X", Msg);
    HTREEITEM hTr, hTr2;

    switch (Msg)
        {
        case WM_CREATE:         //윈도우가 생성될 때 한번 옴
            CreateWindow(/*WC_TREEVIEW*/"SysTreeView32", "", TVS_SHOWSELALWAYS|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|WS_CHILD|WS_VISIBLE|WS_BORDER,
                      10, 10, 800-30-100, 600-50,
                      (HWND)hWnd, (HMENU)TreeViewID, HInst, NULL);

            CreateWindow("BUTTON", "삭제", WS_CHILD|WS_VISIBLE,
                      800-30-100+20, 10, 80, 40,
                      (HWND)hWnd, (HMENU)DeleteItemBtnID, HInst, NULL);

            hTr=TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "서브1-1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "서브1-1", 0);
                hTr2=TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "서브1-1", 0);
                    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "서브1-1-1", 0);
                    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "서브1-1-2", 0);
                    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "서브1-1-3", 0);

            hTr=TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인2", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "서브2-1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "서브2-1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "서브2-1", 0);
            TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인3", 0);
            TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "메인4", 0);


            Ret0:
            return 0;

        case WM_DESTROY:        //윈도우가 파기될 때
            PostQuitMessage(0); //GetMessage()의 리턴을 FALSE로 만들어 종료하게 함
            goto Ret0;

        case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
            {
            PAINTSTRUCT PS;

            BeginPaint(hWnd, &PS);
            DrawAll(hWnd, PS.hdc);
            EndPaint(hWnd, &PS);
            goto Ret0;
            }

        case WM_SIZE:           //윈도우 크기의 변화가 생겼을 때
                                //LOWORD(lPrm): Client Width, HIWORD(lPrm): Client Height
            goto Ret0;

        case WM_COMMAND:        //메뉴를 클릭했을 때
            switch (LOWORD(wPrm))
                {
                case DeleteItemBtnID:
                    if ((hTr=TV_GetCurSel(hWnd, TreeViewID))==NULL)
                        {
                        MessageBox(hWnd, "지울 항목을 선택하세요", AppTitle, MB_OK);
                        break;
                        }
                    TV_DeleteItem(hWnd, TreeViewID, hTr);
                }
            goto Ret0;

        case WM_KEYDOWN:        //키를 눌렀을 때
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
//      VC로 컴파일 했을 때 실행파일에서 제일 먼저 호출되는 함수
//      링크 옵션에서 /NODEFAULTLIB 를 주어야 호출됨
//-----------------------------------------------------------------------------
int WinMainCRTStartup()
    {
    int Rslt;
    STARTUPINFO SI;

    SI.dwFlags=0;
    GetStartupInfo(&SI);
    Rslt=WinMain(GetModuleHandle(NULL), 0, GetCommandLine(),
        SI.dwFlags & STARTF_USESHOWWINDOW ? SI.wShowWindow:SW_SHOWDEFAULT);

    ExitProcess(Rslt);
    return Rslt;
    }
#endif

