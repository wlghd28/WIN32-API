#pragma
#include "framework.h"
#include "ChildDialog4.h"

// �Լ� ����
//-----------------------------------------------------------------------------
//       �ڽ� ���̾�α�2 �޼��� ó��
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ChildDialog4_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitChildDialog4(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_ChildDialog4(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_ChildDialog4(hDlg, message, wParam, lParam);
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR WINAPI InitChildDialog4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect_Client;
    GetClientRect(GetParent(hDlg), &rect_Client);
    MoveWindow(hDlg, 0, 50, rect_Client.right - rect_Client.left, rect_Client.bottom - rect_Client.top, TRUE);
    ShowWindow(hDlg, SW_HIDE);

    return TRUE;
}

//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�2 WM_COMMAND �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_ChildDialog4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�2 WM_NOTIFY �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}