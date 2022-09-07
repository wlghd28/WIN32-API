#include "framework.h"
#include "PreferColor.h"

//-----------------------------------------------------------------------------
//      Į���� ������Ƽ ������ ��ȭ���� Proc
//-----------------------------------------------------------------------------
DLGFNC(PreferColorDlgProc)
{
    int I;

    switch (Msg)
    {
    case WM_INITDIALOG:
        //���� ��ȭ���� ó���� ����
        return TRUE;

    case WM_NOTIFY:
        switch (((NMHDR*)lPrm)->code)
        {
        case PSN_SETACTIVE:     //�� Tab�� ���� ��
            PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK | PSWIZB_FINISH);
            PreferPropSheetPage = 0;
            break;

        case PSN_KILLACTIVE:    //�� TAB�� ���� ��
            I = FALSE;
            //�Է��� ���� ������ �ִ� ��� I=TRUE ����
            SetWindowLong(hWnd, DWL_MSGRESULT, I);      //DWL_MSGRESULT�� TRUE�� �Է��ϸ� �� �������� ������ ����
            return TRUE;                                //TRUE�� �������� ������ ���� ���� �ص� �ҿ����

        case PSN_APPLY:         //Ȯ���� ������ �� (������ ���� �ִ� ������ ���׸� ��)
            //�Է��� ���� ������ ����
            MessageBox(hWnd, "0������", AppTitle, MB_OK);
            break;

        case PSN_RESET:         //���Ű�� ���� (������ ���� �ִ� ������ ���׸� ��)
            MessageBox(hWnd, "0������", AppTitle, MB_OK);
            break;
        }
        break;

    case WM_COMMAND:
        //���� ��ȭ���� ó���� ����
        SendMessage(GetParent(hWnd), PSM_CHANGED, (WPARAM)hWnd, 0);     //�����ư�� Ȱ��ȭ��
        return TRUE;
    }

    return FALSE;
}

