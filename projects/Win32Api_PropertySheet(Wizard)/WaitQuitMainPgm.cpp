#include "framework.h"
#include "WaitQuitMainPgm.h"

//-----------------------------------------------------------------------------
//      ���������� �������� üũ ����
//-----------------------------------------------------------------------------
DLGFNC(WaitQuitMainPgmDlgProc)
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
            CurrentPage = 1;  //���� ������ ��ȣ ����

            //SendMessage(GetParent(hWnd), PSM_SETTITLE, 0, (LPARAM)"�ٲ� Ÿ��Ʋ");
            //PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_NEXT);                  //ù������ �� ��
            PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK | PSWIZB_NEXT);        //�߰������� �� ��
            //PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK|PSWIZB_FINISH);    //������������ �� ��
            //PostMessage(GetParent(hWnd), PSM_PRESSBUTTON, PageDirect==0 ? PSBTN_BACK:PSBTN_NEXT, 0);  //�� �������� �ǳʶ� ��

            //���� �������� ��ŵ
            PostMessage(GetParent(hWnd), PSM_PRESSBUTTON, PageDirect == 0 ? PSBTN_BACK : PSBTN_NEXT, 0);
            return TRUE;

        case PSN_KILLACTIVE:
            SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);
            return TRUE;

        case PSN_RESET:         //���������� �ѹ��̶� ���� �� ��ҹ�ư�� ������ �� (�ٸ� ���������� ������ ��)
            //�Ҵ��ڿ�����
            //SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);
            if (CurrentPage == 1) //�ݱ� ��ư�� ������ �� ���� ������������ ��ȭ���ڸ� ���� ������
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


