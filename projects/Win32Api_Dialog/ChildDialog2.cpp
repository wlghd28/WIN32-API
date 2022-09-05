#pragma
#include "framework.h"
#include "ChildDialog2.h"
#include "TestDialogID.h"

extern HINSTANCE    hInst;
HWND                hWndModalless;

// �Լ� ����
//-----------------------------------------------------------------------------
//       �ڽ� ���̾�α�2 �޼��� ó��
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

    case WM_PAINT:          //ȭ���� �׷��� �� ������ ������ ��
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
//      �ڽ� ���̾�α�2 WM_COMMAND �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {
    case IDC_BUTTON_CHILD2_MODAL:      //����� ��ȭ����
        DialogBox(hInst, MAKEINTRESOURCE(TestDialogID), hDlg, ModalTestDlgProc);
        break;

    case IDC_BUTTON_CHILD2_MODALESS:  //��޸����� ��ȭ����
        if (hWndModalless != NULL) break;
        hWndModalless = CreateDialog(hInst, MAKEINTRESOURCE(TestDialogID), hDlg, ModallessTestDlgProc);
        break;

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�2 WM_NOTIFY �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}

