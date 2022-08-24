#include "WinMain.h"
/*
    프로젝트 속성의 링크 옵션 항목에 따라서 프로그램이 실행될 때 호출되는 첫 진입점이 달라짐.
    /SUBSYSTEM:CONSOLE => mainCRTStartup / wmainCRTStartup => main / wmain
    /SUBSYSTEM:WINDOWS => WinMainCRTStartup / wWinMainCRTStartup => WinMain / wWinMain
    /DLL => _DllMainCRTStartup => DllMain
*/


//// WinMain.cpp
//--------------------------------------------------------------------------------------
//  윈도우 어플리케이션 메인
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
{
    MessageBox(NULL, _T("WinMain"), _T("메시지 박스"), MB_OK);
    return 0;
}


//--------------------------------------------------------------------------------------
//  VC로 컴파일 했을 때 실행파일에서 제일 먼저 호출되는 함수.

//  프로젝트 속성의 링크 옵션에서 /NODEFAULTLIB 를 주어야 호출됨.

//  C-Runtime 라이브러리의 불일치 때문에 에러가 날 경우 
//  프로젝트 속성으로 이동하여 구성 속성 > C/C++ > 모든 옵션 > 기본 런타임 검사 옵션을 '기본값'으로 설정한다.

//  __security_init_cookie 함수호출로 인한 전역 보안 쿠키 /GS(버퍼 보안 검사) 에러가 날 경우 
//  프로젝트 속성으로 이동하여 구성 속성 > C/C++ > 모든 옵션 > 보안검사 옵션을 '사용안함'으로 설정한다.
//--------------------------------------------------------------------------------------
int WinMainCRTStartup(void)
{

    MessageBox(NULL, _T("WinMainCRTStartup"), _T("메시지 박스"), MB_OK);

    int iRet;
    STARTUPINFO SI;
    SI.dwFlags = 0;
    GetStartupInfo(&SI);
    iRet = WinMain
    (
        GetModuleHandle(0),
        0,
        GetCommandLine(),
        SI.dwFlags & STARTF_USESHOWWINDOW ? SI.wShowWindow : SW_SHOWDEFAULT
    );

    ExitProcess(iRet);

    return iRet;
}
