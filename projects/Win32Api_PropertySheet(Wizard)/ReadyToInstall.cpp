#include "framework.h"
#include "ReadyToInstall.h"

//-----------------------------------------------------------------------------
//      ��ġ�غ� �Ϸ� ����
//-----------------------------------------------------------------------------
DLGFNC(ReadyToInstallDlgProc)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        //���� ��ȭ���� ó���� ����
        return TRUE;

    case WM_NOTIFY:
        switch (((NMHDR*)lPrm)->code)
        {
        case PSN_SETACTIVE: //�� Tab�� ���� ��
            CurrentPage = 4;  //���� ������ ��ȣ ����

            //SendMessage(GetParent(hWnd), PSM_SETTITLE, 0, (LPARAM)"�ٲ� Ÿ��Ʋ");
            //PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_NEXT);                  //ù������ �� ��
            PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK | PSWIZB_NEXT);        //�߰������� �� ��
            //PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK|PSWIZB_FINISH);    //������������ �� ��
            //PostMessage(GetParent(hWnd), PSM_PRESSBUTTON, PageDirect==0 ? PSBTN_BACK:PSBTN_NEXT, 0);  //�� �������� �ǳʶ� ��
            return TRUE;

        case PSN_KILLACTIVE:
            SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);
            return TRUE;

        case PSN_RESET:         //���������� �ѹ��̶� ���� �� ��ҹ�ư�� ������ �� (�ٸ� ���������� ������ ��)
            //�Ҵ��ڿ�����
            //SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);
            if (CurrentPage == 4) //�ݱ� ��ư�� ������ �� ���� ������������ ��ȭ���ڸ� ���� ������
            {
                if (MessageBox(GetParent(hWnd), "��ġ���� �ʰ� �����մϴ�.", AppTitle, MB_OKCANCEL) != IDOK)
                    SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);   //�������� ����
            }
            return TRUE;

        case PSN_WIZBACK:
            PageDirect = 0;
            return TRUE;

        case PSN_WIZNEXT:
            //��Ʈ���� ���� �о ����
            //SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);    //������������ �Ȱ�
            //SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);     //�̷��� �ϸ� ���������� ��
            PageDirect = 1;
            return TRUE;

        case PSN_WIZFINISH:     //������Ƽ â�� ���� ��
            return TRUE;
        }
    }
    return FALSE;
}



