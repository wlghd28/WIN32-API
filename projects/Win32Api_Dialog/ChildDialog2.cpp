#pragma
#include "framework.h"
#include "ChildDialog2.h"
#include "TestDialogID.h"

extern HINSTANCE    hInst;
HWND                hWndModalless;

// 함수 정의
//-----------------------------------------------------------------------------
//       자식 다이얼로그2 메세지 처리
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ChildDialog2_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitChildDialog2(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_ChildDialog2(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_ChildDialog2(hDlg, message, wParam, lParam);
        break;

    case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
    {
        PAINTSTRUCT ps;

        BeginPaint(hDlg, &ps);
        DrawAll(hDlg, ps.hdc);
        EndPaint(hDlg, &ps);
    }
        break;



    }
    return (INT_PTR)FALSE;
}

INT_PTR WINAPI InitChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect_Client;
    GetClientRect(GetParent(hDlg), &rect_Client);
    MoveWindow(hDlg, 0, 50, rect_Client.right - rect_Client.left, rect_Client.bottom - rect_Client.top, TRUE);
    ShowWindow(hDlg, SW_HIDE);

    return TRUE;
}

//-----------------------------------------------------------------------------
//      자식 다이얼로그2 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {
    case IDC_BUTTON_CHILD2_MODAL:      //모달형 대화상자
        DialogBox(hInst, MAKEINTRESOURCE(TestDialogID), hDlg, ModalTestDlgProc);
        break;

    case IDC_BUTTON_CHILD2_MODALESS:  //모달리스형 대화상자
        if (hWndModalless != NULL) break;
        hWndModalless = CreateDialog(hInst, MAKEINTRESOURCE(TestDialogID), hDlg, ModallessTestDlgProc);
        break;

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      자식 다이얼로그2 WM_NOTIFY 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}

