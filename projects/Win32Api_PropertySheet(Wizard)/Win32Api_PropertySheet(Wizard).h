#pragma once

#include "resource.h"


// ���� ����:
static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
static CONST CHAR AppTitle[] = "���α׷� ��ġ";
static int CurrentPage;
static int PageDirect = 1;    //0�̸� ������, 1�̸� ��������

#define WMCMDID LOWORD(wPrm)
#define LOCAL(Type) static Type WINAPI
#define countof(S) (sizeof(S)/sizeof(S[0]))
#define DLGFNC(DlgProc) BOOL CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)


// �Լ�����
BOOL InitInstance(HINSTANCE, int);
LOCAL(int) CreateExpert(HWND hWndOwner, LPCSTR lpTitle);
LOCAL(VOID) SetPropertyPage(PROPSHEETPAGE* PSP, int DlgID, DLGPROC DlgProc, LPCSTR Title);
VOID Printf(LPCSTR FormStr, ...);