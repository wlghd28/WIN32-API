#pragma once

#include "resource.h"

// 전역변수 선언
static HINSTANCE hInst;                                // 현재 인스턴스입니다.
static CONST CHAR AppTitle[] = "옵션 설정";
static int  PreferPropSheetPage;        //최종 열렸던 페이지 번호를 저장

#define WMCMDID LOWORD(wPrm)
#define LOCAL(Type) static Type WINAPI
#define countof(S) (sizeof(S)/sizeof(S[0]))
#define DLGFNC(DlgProc) BOOL CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)

// 함수 선언
BOOL InitInstance(HINSTANCE, int);
LOCAL(BOOL) SetPreference(HWND hWnd);
LOCAL(VOID) SetPropsheetPage(PROPSHEETPAGE* PSP, DLGPROC DlgProc, int DlgID);
VOID Printf(LPCSTR FormStr, ...);