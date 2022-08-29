#pragma once
#include "resource.h"

// 함수 선언
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr);
int WINAPI LB_AddString(HWND hWnd, int LBID, LPCSTR ToAddStr);
int WINAPI LB_GetCurSel(HWND hWnd, int LBID);
int WINAPI LB_DeleteString(HWND hWnd, int LBID, int ToDelIdx);
int WINAPI LB_GetCount(HWND hWnd, int LBID);
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr);

void WINAPI CreateControl(HWND hWnd);
