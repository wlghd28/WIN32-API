#include "framework.h"
#include "MainDialog.h"

#include "ChildDialog1.h"
#include "ChildDialog2.h"
#include "ChildDialog3.h"
#include "ChildDialog4.h"

extern HINSTANCE hInst;

HWND hWnd_Child1;
HWND hWnd_Child2;
HWND hWnd_Child3;
HWND hWnd_Child4;

// 메인 다이얼로그 함수 정의
// 
//-----------------------------------------------------------------------------
//      메인 다이얼로그 초기화
//-----------------------------------------------------------------------------
INT_PTR WINAPI InitMainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 다이얼로그 크기 설정
    RECT rect_Client;
    GetClientRect(GetParent(hDlg), &rect_Client);
    MoveWindow(hDlg, 0, 0, rect_Client.right - rect_Client.left, rect_Client.bottom - rect_Client.top, TRUE);
    ShowWindow(hDlg, SW_SHOW);

    // 부모 탭 컨트롤 초기화
    TCITEM Tab_Main_Parent;
    Tab_Main_Parent.mask = TCIF_TEXT;
    Tab_Main_Parent.pszText = (LPSTR)"Dialog1";
    SendDlgItemMessage(hDlg, IDC_TAB_MAIN_PARENT, TCM_INSERTITEM, 0, (LPARAM)&Tab_Main_Parent);

    Tab_Main_Parent.pszText = (LPSTR)"Dialog2";
    SendDlgItemMessage(hDlg, IDC_TAB_MAIN_PARENT, TCM_INSERTITEM, 1, (LPARAM)&Tab_Main_Parent);

    Tab_Main_Parent.pszText = (LPSTR)"Dialog3";
    SendDlgItemMessage(hDlg, IDC_TAB_MAIN_PARENT, TCM_INSERTITEM, 2, (LPARAM)&Tab_Main_Parent);

    Tab_Main_Parent.pszText = (LPSTR)"Dialog4";
    SendDlgItemMessage(hDlg, IDC_TAB_MAIN_PARENT, TCM_INSERTITEM, 3, (LPARAM)&Tab_Main_Parent);


    // 자식 다이얼로그 생성

    // 다이얼로그 1
    hWnd_Child1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHILD_DIALOG1), hDlg, ChildDialog1_CmdProc);

    // 다이얼로그 2
    hWnd_Child2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHILD_DIALOG2), hDlg, ChildDialog2_CmdProc);

    // 다이얼로그 3
    hWnd_Child3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHILD_DIALOG3), hDlg, ChildDialog3_CmdProc);

    // 다이얼로그 4
    hWnd_Child4 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHILD_DIALOG4), hDlg, ChildDialog4_CmdProc);


    return TRUE;
}

//-----------------------------------------------------------------------------
//      메인 다이얼로그 메세지 처리
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDialog_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitMainDialog(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_MainDialog(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_MainDialog(hDlg, message, wParam, lParam);
        break;
    }
    return (INT_PTR)FALSE;
}

//-----------------------------------------------------------------------------
//      메인 다이얼로그 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_MainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {
    case IDC_TAB_MAIN_PARENT:
        break;

    case ModalDialogCmdID:      //모달형 대화상자
        WM_CmdProc_ChildDialog2(hDlg, message, wParam, lParam);
        break;

    case ModallessDialogCmdID:  //모달리스형 대화상자
        WM_CmdProc_ChildDialog2(hDlg, message, wParam, lParam);
        break;


    default:
        break;
    }
}

//-----------------------------------------------------------------------------
//      메인 다이얼로그 WM_NOTIFY 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_MainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {
    case IDC_TAB_MAIN_PARENT:
    {
        LPNMHDR lpnmhdr = (LPNMHDR)lParam;

        switch (lpnmhdr->code)
        {
        case TCN_SELCHANGE:
            switch (SendDlgItemMessage(hDlg, IDC_TAB_MAIN_PARENT, TCM_GETCURSEL, 0, 0))
            {
            case 0:
                ShowWindow(hWnd_Child1, SW_SHOW);
                ShowWindow(hWnd_Child2, SW_HIDE);
                ShowWindow(hWnd_Child3, SW_HIDE);
                ShowWindow(hWnd_Child4, SW_HIDE);
                break;
            case 1:
                ShowWindow(hWnd_Child1, SW_HIDE);
                ShowWindow(hWnd_Child2, SW_SHOW);
                ShowWindow(hWnd_Child3, SW_HIDE);
                ShowWindow(hWnd_Child4, SW_HIDE);
                break;
            case 2:
                ShowWindow(hWnd_Child1, SW_HIDE);
                ShowWindow(hWnd_Child2, SW_HIDE);
                ShowWindow(hWnd_Child3, SW_SHOW);
                ShowWindow(hWnd_Child4, SW_HIDE);
                break;
            case 3:
                ShowWindow(hWnd_Child1, SW_HIDE);
                ShowWindow(hWnd_Child2, SW_HIDE);
                ShowWindow(hWnd_Child3, SW_HIDE);
                ShowWindow(hWnd_Child4, SW_SHOW);
                break;

            default:
                break;
            }

            break;
        }
    }
        break;

    default:
        break;
    }

}