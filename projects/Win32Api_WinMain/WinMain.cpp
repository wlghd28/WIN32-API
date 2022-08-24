#include "WinMain.h"
/*
    ������Ʈ �Ӽ��� ��ũ �ɼ� �׸� ���� ���α׷��� ����� �� ȣ��Ǵ� ù �������� �޶���.
    /SUBSYSTEM:CONSOLE => mainCRTStartup / wmainCRTStartup => main / wmain
    /SUBSYSTEM:WINDOWS => WinMainCRTStartup / wWinMainCRTStartup => WinMain / wWinMain
    /DLL => _DllMainCRTStartup => DllMain
    
    �� ������Ʈ�� ������Ʈ�� ���� ���� �� WINAPI �Լ��� �� �� ��������� ���� ���״µ��� LNK2019 ������ ���ٸ�
    Visual Studio�� �ֽ� ǥ�� ���̺귯�� ���濡 ���� �߰��ؾ� �� ���̺귯������ �߰��Ʊ� �����̴�.
    ���� msvcrt.lib, ucrt.lib, vcruntime.lib 3���� ���̺귯���� �߰� ���Ӽ��� �߰� ������� �Ѵ�.
*/

//// WinMain.cpp
//--------------------------------------------------------------------------------------
//  ������ ���ø����̼� ����
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR CmdPrm, int CmdShow)
{
    //MessageBox(NULL, _T("WinMain"), _T("�޽��� �ڽ�"), MB_OK);
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
//  VC�� ������ ���� �� �������Ͽ��� ���� ���� ȣ��Ǵ� �Լ�.

//  ������Ʈ �Ӽ��� ��ũ �ɼǿ��� /NODEFAULTLIB �� �־�� ȣ���.

//  C-Runtime ���̺귯���� ����ġ ������ ������ �� ��� 
//  ������Ʈ �Ӽ����� �̵��Ͽ� ���� �Ӽ� > C/C++ > ��� �ɼ� > �⺻ ��Ÿ�� �˻� �ɼ��� '�⺻��'���� �����Ѵ�.

//  __security_init_cookie �Լ�ȣ��� ���� ���� ���� ��Ű /GS(���� ���� �˻�) ������ �� ��� 
//  ������Ʈ �Ӽ����� �̵��Ͽ� ���� �Ӽ� > C/C++ > ��� �ɼ� > ���Ȱ˻� �ɼ��� '������'���� �����Ѵ�.
//--------------------------------------------------------------------------------------
int WinMainCRTStartup(void)
{
    //MessageBox(NULL, _T("WinMainCRTStartup"), _T("�޽��� �ڽ�"), MB_OK);

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
//  ��ũ�� ����� �Լ�
//--------------------------------------------------------------------------------------
void Printf(LPCSTR FormStr, ...)  // ��ũ�� ����� �Լ� (��������)
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