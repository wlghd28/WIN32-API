#pragma once
#include "resource.h"

// 함수 선언
INT_PTR CALLBACK ChildDialog2_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


VOID Printf_Child2(LPCSTR FormStr, ...);
LPCSTR WINAPI SkipSpace(LPCSTR lp);
LPCSTR WINAPI NextWord(LPCSTR lp, int WordCnt);
VOID WINAPI DrawAll(HWND hWnd, HDC hDC);
BOOL WINAPI ModalTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);
BOOL WINAPI ModallessTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);
