#pragma
#include "framework.h"
#include "ChildDialog3.h"

// 함수 정의
//-----------------------------------------------------------------------------
//       자식 다이얼로그2 메세지 처리
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ChildDialog3_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitChildDialog3(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_ChildDialog3(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_ChildDialog3(hDlg, message, wParam, lParam);
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR WINAPI InitChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
void WINAPI WM_CmdProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      자식 다이얼로그2 WM_NOTIFY 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}