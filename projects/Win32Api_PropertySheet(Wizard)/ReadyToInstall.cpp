#include "framework.h"
#include "ReadyToInstall.h"

//-----------------------------------------------------------------------------
//      설치준비 완료 시작
//-----------------------------------------------------------------------------
DLGFNC(ReadyToInstallDlgProc)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        //기존 대화상자 처리와 동일
        return TRUE;

    case WM_NOTIFY:
        switch (((NMHDR*)lPrm)->code)
        {
        case PSN_SETACTIVE: //이 Tab이 열릴 때
            CurrentPage = 4;  //현재 페이지 번호 설정

            //SendMessage(GetParent(hWnd), PSM_SETTITLE, 0, (LPARAM)"바꿀 타이틀");
            //PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_NEXT);                  //첫페이지 일 때
            PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK | PSWIZB_NEXT);        //중간페이지 일 때
            //PostMessage(GetParent(hWnd), PSM_SETWIZBUTTONS, 0, PSWIZB_BACK|PSWIZB_FINISH);    //마지막페이지 일 때
            //PostMessage(GetParent(hWnd), PSM_PRESSBUTTON, PageDirect==0 ? PSBTN_BACK:PSBTN_NEXT, 0);  //이 페이지를 건너뛸 때
            return TRUE;

        case PSN_KILLACTIVE:
            SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);
            return TRUE;

        case PSN_RESET:         //이페이지가 한번이라도 열린 후 취소버튼을 눌렀을 때 (다른 페이지에서 눌러도 옴)
            //할당자원해제
            //SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);
            if (CurrentPage == 4) //닫기 버튼을 눌렀을 때 현재 페이지에서만 대화상자를 띄우기 위함임
            {
                if (MessageBox(GetParent(hWnd), "설치하지 않고 종료합니다.", AppTitle, MB_OKCANCEL) != IDOK)
                    SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);   //종료하지 않음
            }
            return TRUE;

        case PSN_WIZBACK:
            PageDirect = 0;
            return TRUE;

        case PSN_WIZNEXT:
            //콘트롤의 값을 읽어서 보관
            //SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);    //다음페이지로 안감
            //SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);     //이렇게 하면 뒷페이지로 감
            PageDirect = 1;
            return TRUE;

        case PSN_WIZFINISH:     //프로퍼티 창이 닫힐 때
            return TRUE;
        }
    }
    return FALSE;
}



