// Win32Api_Dialog.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "framework.h"
#include "Win32Api_Dialog.h"

// 메인 다이얼로그
#include "MainDialog.h"

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
BOOL                InitInstance(HINSTANCE, int);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    // 공용 컨트롤 초기화
    InitCommonControls();




    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    return 0;

}


//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, MainDialog_CmdProc);

   return TRUE;
}
