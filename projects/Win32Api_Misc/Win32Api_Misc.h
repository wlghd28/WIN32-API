#pragma once
#pragma comment(lib,"Comctl32.lib")

#include "resource.h"
#include <CommCtrl.h>

// �Լ� ����
void WINAPI CreateControl(HWND hWnd);

void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

static VOID WINAPI DrawAll(HWND hWnd, HDC hDC);