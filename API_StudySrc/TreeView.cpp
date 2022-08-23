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
#include <Commctrl.h>   //TreeView
#define SCREENDEBUG 1

static CONST CHAR AppTitle[]="WIN32 ���� ������ â ���ø�";
static CONST CHAR MainWindowClassName[]="MainWnd";

static HINSTANCE HInst;


#define TreeViewID          100
#define DeleteItemBtnID     101



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



//-----------------------------------------------------------------------------
//      TreeView�� Item�� �����մϴ�
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
//      �־��� TV Item�� ������
//-----------------------------------------------------------------------------
BOOL WINAPI TV_DeleteItem(HWND hWnd, int TVID, HTREEITEM hItem)
    {
    if (TVID!=0) hWnd=GetDlgItem(hWnd, TVID);
    return (BOOL)SendMessage(hWnd, TVM_DELETEITEM, 0, (LPARAM)hItem);
    }



//-----------------------------------------------------------------------------
//      TreeView�� ���缱�õ� �׸��� ����ϴ� (�����ϸ� Null) TreeView_GetSelection()
//-----------------------------------------------------------------------------
HTREEITEM WINAPI TV_GetCurSel(HWND hWnd, int TVID)
    {
    if (TVID!=0) hWnd=GetDlgItem(hWnd, TVID);
    return (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_CARET, NULL);
    }



//-----------------------------------------------------------------------------
//      ���� ������ �޼��� ó��
//-----------------------------------------------------------------------------
static LRESULT WINAPI MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
    {
    //Printf("Msg=%X", Msg);
    HTREEITEM hTr, hTr2;

    switch (Msg)
        {
        case WM_CREATE:         //�����찡 ������ �� �ѹ� ��
            CreateWindow(/*WC_TREEVIEW*/"SysTreeView32", "", TVS_SHOWSELALWAYS|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|WS_CHILD|WS_VISIBLE|WS_BORDER,
                      10, 10, 800-30-100, 600-50,
                      (HWND)hWnd, (HMENU)TreeViewID, HInst, NULL);

            CreateWindow("BUTTON", "����", WS_CHILD|WS_VISIBLE,
                      800-30-100+20, 10, 80, 40,
                      (HWND)hWnd, (HMENU)DeleteItemBtnID, HInst, NULL);

            hTr=TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "����1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "����1-1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "����1-1", 0);
                hTr2=TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "����1-1", 0);
                    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "����1-1-1", 0);
                    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "����1-1-2", 0);
                    TV_InsertItem(hWnd, TreeViewID, hTr2, TVI_LAST, "����1-1-3", 0);

            hTr=TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "����2", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "����2-1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "����2-1", 0);
                TV_InsertItem(hWnd, TreeViewID, hTr, TVI_LAST, "����2-1", 0);
            TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "����3", 0);
            TV_InsertItem(hWnd, TreeViewID, NULL, TVI_LAST, "����4", 0);


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
                case DeleteItemBtnID:
                    if ((hTr=TV_GetCurSel(hWnd, TreeViewID))==NULL)
                        {
                        MessageBox(hWnd, "���� �׸��� �����ϼ���", AppTitle, MB_OK);
                        break;
                        }
                    TV_DeleteItem(hWnd, TreeViewID, hTr);
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
    Rslt=WinMain(GetModuleHandle(NULL), 0, GetCommandLine(),
        SI.dwFlags & STARTF_USESHOWWINDOW ? SI.wShowWindow:SW_SHOWDEFAULT);

    ExitProcess(Rslt);
    return Rslt;
    }
#endif

