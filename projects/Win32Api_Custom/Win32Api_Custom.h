#pragma once

#include "resource.h"

// 함수선언
void WINAPI Regist7Segment();
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_Timer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI CreateControl(HWND hWnd);

HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName);
void WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY, int CopyMode);

static void WINAPI DrawAll(HWND hWnd, HDC hDC);
static void WINAPI DrawSevenSegment(HWND hWnd, HDC hDC);
