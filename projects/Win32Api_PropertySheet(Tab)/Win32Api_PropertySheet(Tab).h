#pragma once

#include "resource.h"

// �������� ����
static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
static CONST CHAR AppTitle[] = "�ɼ� ����";
static int  PreferPropSheetPage;        //���� ���ȴ� ������ ��ȣ�� ����

#define WMCMDID LOWORD(wPrm)
#define LOCAL(Type) static Type WINAPI
#define countof(S) (sizeof(S)/sizeof(S[0]))
#define DLGFNC(DlgProc) BOOL CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)

// �Լ� ����
BOOL InitInstance(HINSTANCE, int);
LOCAL(BOOL) SetPreference(HWND hWnd);
LOCAL(VOID) SetPropsheetPage(PROPSHEETPAGE* PSP, DLGPROC DlgProc, int DlgID);
VOID Printf(LPCSTR FormStr, ...);