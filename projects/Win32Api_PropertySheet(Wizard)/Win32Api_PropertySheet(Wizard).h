#pragma once

#include "resource.h"


// 전역 변수:
static HINSTANCE hInst;                                // 현재 인스턴스입니다.
static CONST CHAR AppTitle[] = "프로그램 설치";
static int CurrentPage;
static int PageDirect = 1;    //0이면 앞으로, 1이면 다음으로

#define WMCMDID LOWORD(wPrm)
#define LOCAL(Type) static Type WINAPI
#define countof(S) (sizeof(S)/sizeof(S[0]))
#define DLGFNC(DlgProc) BOOL CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)


// 함수선언
BOOL InitInstance(HINSTANCE, int);
LOCAL(int) CreateExpert(HWND hWndOwner, LPCSTR lpTitle);
LOCAL(VOID) SetPropertyPage(PROPSHEETPAGE* PSP, int DlgID, DLGPROC DlgProc, LPCSTR Title);
VOID Printf(LPCSTR FormStr, ...);