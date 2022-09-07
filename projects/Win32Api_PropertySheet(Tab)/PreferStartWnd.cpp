#include "framework.h"
#include "PreferStartWnd.h"


//-----------------------------------------------------------------------------
//      윈도우시작설정 프라퍼티 페이지 대화상자 Proc
//-----------------------------------------------------------------------------
DLGFNC(PreferStartWndDlgProc)
{
    int I;

    switch (Msg)
    {
    case WM_INITDIALOG:
        //기존 대화상자 처리와 동일
        return TRUE;

    case WM_NOTIFY:
        switch (((NMHDR*)lPrm)->code)
        {
        case PSN_SETACTIVE:     //이 Tab이 열릴 때
            PreferPropSheetPage = 2;
            break;

        case PSN_KILLACTIVE:    //이 TAB이 닫힐 때
            I = FALSE;
            //입력한 값이 문제가 있는 경우 I=TRUE 설정
            SetWindowLong(hWnd, DWL_MSGRESULT, I);      //DWL_MSGRESULT에 TRUE를 입력하면 이 페이지를 떠나지 않음
            return TRUE;                                //TRUE를 리턴하지 않으면 위와 같이 해도 소용없음

        case PSN_APPLY:         //확인을 눌렀을 때
            //입력한 값을 꺼내서 저장
            MessageBox(hWnd, "2페이지", AppTitle, MB_OK);
            break;

        case PSN_RESET:         //취소키를 누름
            MessageBox(hWnd, "2페이지", AppTitle, MB_OK);
            break;
        }
        break;

    case WM_COMMAND:
        //기존 대화상자 처리와 동일
        return TRUE;
    }

    return FALSE;
}

