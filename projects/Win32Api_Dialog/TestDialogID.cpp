#include "framework.h"
#include "TestDialogID.h"

#define SCREENDEBUG 999

extern HINSTANCE hInst;

CONST CHAR         AppTitle[] = "WIN32 ���� ������ â ���ø�";
extern HWND        hWndModalless;



//-----------------------------------------------------------------------------
//      ��ũ�� ����� �Լ�
//-----------------------------------------------------------------------------
VOID Printf_Child2(LPCSTR FormStr, ...)
{
    HDC  hDC;
    va_list VL;
    CHAR Buff[MAX_PATH];
#if SCREENDEBUG
    static int  DebugPosY = 0;
#endif

    va_start(VL, FormStr);
    wvnsprintf(Buff, sizeof(Buff), FormStr, VL);
    va_end(VL);

#if SCREENDEBUG
    hDC = GetDC(NULL);
    TextOut(hDC, 0, DebugPosY, Buff, lstrlen(Buff));
    ReleaseDC(NULL, hDC);
    if ((DebugPosY += 16) >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;
#else
    OutputDebugString(Buff);
#endif
    //DebugFile("%s\r\n",Buff);
}




//-----------------------------------------------------------------------------
//              ������ Skip��
//-----------------------------------------------------------------------------
LPCSTR WINAPI SkipSpace(LPCSTR lp)
{
    UCHAR Cha;

    for (;;)
    {
        Cha = *(BYTE*)lp;
        if (Cha == 0 || Cha > ' ') break;
        lp++;
    }
    return lp;
}




//-----------------------------------------------------------------------------
//      ���� �ܾ��� ��ġ�� �ݴϴ� (�����̳� TAB����)
//      ����ܾ�� ������ ���� ���� �ܾ��� ��ġ�� �ݴϴ�
//      ������ġ�� �����̸� �ٷ� ���� ������ �ܾ�
//      '�� "�� ���ΰ�� �ϳ��� �ܾ�� �ν��մϴ�
//-----------------------------------------------------------------------------
LPCSTR WINAPI NextWord(LPCSTR lp, int WordCnt)
{
    int Cha, FirstCha;

    for (;;)
    {
        lp = SkipSpace(lp);       //���齺ŵ
        FirstCha = lp[0];
        if (FirstCha == 0 || WordCnt == 0) break;
        WordCnt--;

        if (FirstCha == 0x27 || FirstCha == 0x22) lp++;     //"'", '"'
        else FirstCha = 0;

        for (;;)                        //�ܾŵ
        {
            Cha = *(BYTE*)lp++;
            if (Cha == 0) { lp--; break; }
            if (FirstCha != 0)
            {
                if (FirstCha == Cha) break;
            }
            else {
                if (Cha <= ' ') { lp--; break; }
            }
        }
    }
    return lp;
}




//-----------------------------------------------------------------------------
//      ��� ȭ�� �׸��� ����
//-----------------------------------------------------------------------------
VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    RECT R;
    static CONST CHAR DispText[] = "���� ������ �Դϴ�.";

    GetClientRect(hWnd, &R);
    DrawText(hDC, DispText, lstrlen(DispText), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}




//-----------------------------------------------------------------------------
//      ��� ��ȭ���� ó��
//-----------------------------------------------------------------------------
BOOL WINAPI ModalTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wPrm))
        {
        case IDOK:
            EndDialog(hWnd, IDCANCEL);
            break;
        case IDCANCEL:
            EndDialog(hWnd, IDCANCEL);
            break;
        }
    }
    return FALSE;
}




//-----------------------------------------------------------------------------
//      ��޸��� ��ȭ���� ó��
//-----------------------------------------------------------------------------
BOOL WINAPI ModallessTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        hWndModalless = hWnd;
        ShowWindow(hWndModalless, SW_SHOW);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wPrm))
        {
        case IDOK:
            hWndModalless = NULL;
            DestroyWindow(hWnd);
            break;
        case IDCANCEL:
            hWndModalless = NULL;
            DestroyWindow(hWnd);
        }
    }
    return FALSE;
}


