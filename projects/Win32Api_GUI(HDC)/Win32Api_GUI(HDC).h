#pragma once

#include "resource.h"


// 함수 선언
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);