#include "framework.h"
#include "PreferEtcSet.h"

//-----------------------------------------------------------------------------
//      ��Ÿ���� ������Ƽ ������ ��ȭ���� Proc
//-----------------------------------------------------------------------------
DLGFNC(PreferEtcSetDlgProc)
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
            PreferPropSheetPage = 4;
            break;

        case PSN_KILLACTIVE:    //�� TAB�� ���� ��
            I = FALSE;
            //�Է��� ���� ������ �ִ� ��� I=TRUE ����
            SetWindowLong(hWnd, DWL_MSGRESULT, I);      //DWL_MSGRESULT�� TRUE�� �Է��ϸ� �� �������� ������ ����
            return TRUE;                                //TRUE�� �������� ������ ���� ���� �ص� �ҿ����

        case PSN_APPLY:         //Ȯ���� ������ �� (���� ������ ���� �ִ� ���������Ը� ��)
            //�Է��� ���� ������ ����
            MessageBox(hWnd, "4������", AppTitle, MB_OK);
            break;

        case PSN_RESET:         //���Ű�� ����
            MessageBox(hWnd, "4������", AppTitle, MB_OK);
            break;
        }
        break;

    case WM_COMMAND:
        //���� ��ȭ���� ó���� ����
        return TRUE;
    }

    return FALSE;
}

