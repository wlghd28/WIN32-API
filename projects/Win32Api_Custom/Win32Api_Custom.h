#pragma once

#include "resource.h"
#include "FND.h"
#include "Blank.h"
#include "Bitmap.h"

// 함수선언
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_Timer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);

void WINAPI InitBitmap(HWND hWnd);

void WINAPI DestroyBitmap(HWND hWnd);

static void WINAPI DrawAll(HWND hWnd, HDC hDC);
