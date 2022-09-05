#pragma once
#include "resource.h"

// 함수 선언

VOID Printf_TestDialogID(LPCSTR FormStr, ...);
LPCSTR WINAPI SkipSpace(LPCSTR lp);
LPCSTR WINAPI NextWord(LPCSTR lp, int WordCnt);
VOID WINAPI DrawAll(HWND hWnd, HDC hDC);
BOOL WINAPI ModalTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);
BOOL WINAPI ModallessTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);