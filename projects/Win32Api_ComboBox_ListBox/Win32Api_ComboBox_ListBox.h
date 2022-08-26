#pragma once
#include "resource.h"

// 함수 선언
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow);
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr);
int WINAPI LB_AddString(HWND hWnd, int LBID, LPCSTR ToAddStr);
int WINAPI LB_GetCurSel(HWND hWnd, int LBID);
int WINAPI LB_DeleteString(HWND hWnd, int LBID, int ToDelIdx);
int WINAPI LB_GetCount(HWND hWnd, int LBID);
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr);

void WINAPI CreateControl(HWND hWnd);
