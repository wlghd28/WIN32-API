#include "WinMain.h"
/*
    프로젝트 속성의 링크 옵션 항목에 따라서 프로그램이 실행될 때 호출되는 첫 진입점이 달라짐.
    /SUBSYSTEM:CONSOLE => mainCRTStartup / wmainCRTStartup => main / wmain
    /SUBSYSTEM:WINDOWS => WinMainCRTStartup / wWinMainCRTStartup => WinMain / wWinMain
    /DLL => _DllMainCRTStartup => DllMain
    
    빈 프로젝트로 프로젝트를 생성 했을 때 WINAPI 함수를 쓸 때 헤더파일을 포함 시켰는데도 LNK2019 오류가 난다면
    Visual Studio의 최신 표준 라이브러리 변경에 의해 추가해야 할 라이브러리들이 추가됐기 때문이다.
    따라서 msvcrt.lib, ucrt.lib, vcruntime.lib 3개의 라이브러리를 추가 종속성에 추가 시켜줘야 한다.
*/

//// WinMain.cpp
//--------------------------------------------------------------------------------------
//  윈도우 어플리케이션 메인
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
{
    //MessageBox(NULL, _T("WinMain"), _T("메시지 박스"), MB_OK);
    CHAR Buff[128];
    HINSTANCE hDll1, hDll2;

    hDll1 = LoadLibrary("msimg32.dll");
    hDll2 = LoadLibrary("msimsg.dll");

    Printf("hModule\t = %X\n", GetModuleHandle(NULL));
    Printf("hInst\t = %X\n", hInst);
    Printf("hDll1\t = %X\n", hDll1);
    Printf("hDll2\t = %X\n", hDll2);

    Printf(Buff);
    Printf("Hellow");

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
    //MessageBox(NULL, _T("WinMainCRTStartup"), _T("메시지 박스"), MB_OK);

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



//--------------------------------------------------------------------------------------
//  스크린 디버그 함수
//--------------------------------------------------------------------------------------
void Printf(LPCSTR FormStr, ...)  // 스크린 디버그 함수 (가변인자)
{
    HDC hDC;
    va_list VL;
    CHAR Buff[MAX_PATH];
    static int DebugPosY = 0;

    va_start(VL, FormStr);
    StringCbPrintf(Buff, sizeof(Buff), FormStr, VL);
    va_end(VL);

    hDC = GetDC(NULL);
    TextOut(hDC, 0, DebugPosY, Buff, lstrlen(Buff));
    if ((DebugPosY += 16) >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;

    //OutputDebugString(Buff);
}