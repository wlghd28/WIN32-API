#pragma once

#include "resource.h"


// 함수 선언
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);

void WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY);

HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName);
static void WINAPI DrawAll(HWND hWnd, HDC hDC);