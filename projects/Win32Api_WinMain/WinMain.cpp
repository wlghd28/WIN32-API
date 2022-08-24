#include "WinMain.h"
/*
    ������Ʈ �Ӽ��� ��ũ �ɼ� �׸� ���� ���α׷��� ����� �� ȣ��Ǵ� ù �������� �޶���.
    /SUBSYSTEM:CONSOLE => mainCRTStartup / wmainCRTStartup => main / wmain
    /SUBSYSTEM:WINDOWS => WinMainCRTStartup / wWinMainCRTStartup => WinMain / wWinMain
    /DLL => _DllMainCRTStartup => DllMain
*/


//// WinMain.cpp
//--------------------------------------------------------------------------------------
//  ������ ���ø����̼� ����
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
{
    MessageBox(NULL, _T("WinMain"), _T("�޽��� �ڽ�"), MB_OK);
    return 0;
}


//--------------------------------------------------------------------------------------
//  VC�� ������ ���� �� �������Ͽ��� ���� ���� ȣ��Ǵ� �Լ�.

//  ������Ʈ �Ӽ��� ��ũ �ɼǿ��� /NODEFAULTLIB �� �־�� ȣ���.

//  C-Runtime ���̺귯���� ����ġ ������ ������ �� ��� 
//  ������Ʈ �Ӽ����� �̵��Ͽ� ���� �Ӽ� > C/C++ > ��� �ɼ� > �⺻ ��Ÿ�� �˻� �ɼ��� '�⺻��'���� �����Ѵ�.

//  __security_init_cookie �Լ�ȣ��� ���� ���� ���� ��Ű /GS(���� ���� �˻�) ������ �� ��� 
//  ������Ʈ �Ӽ����� �̵��Ͽ� ���� �Ӽ� > C/C++ > ��� �ɼ� > ���Ȱ˻� �ɼ��� '������'���� �����Ѵ�.
//--------------------------------------------------------------------------------------
int WinMainCRTStartup(void)
{

    MessageBox(NULL, _T("WinMainCRTStartup"), _T("�޽��� �ڽ�"), MB_OK);

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
