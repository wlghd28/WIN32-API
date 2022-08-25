#pragma once

//// Win32Api_Base.h
//#define NODEFAULTLIB
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

// Windows 헤더 파일
#include <Windows.h>
// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//#include <Shlwapi.h>	// wvnsprintf()
#include <strsafe.h>    // StringCbPrintf()


// 함수선언
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hInstPrev,LPSTR CmdPrm,int CmdShow);
void Printf(LPCSTR FormStr, ...);   // 스크린 디버그 함수 (가변인자)
static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);
static void WINAPI DrawInit(HWND hWnd);
static void WINAPI DrawAll(HWND hWnd, HDC hDC);
static void WINAPI DrawDrag(HWND hWnd, COLORREF Col);
void WINAPI DragStart(HWND hWnd, LPARAM lPrm);
void WINAPI DragFinish(HWND hWnd, LPARAM lPrm);
void WINAPI DragMoving(HWND hWnd, LPARAM lPrm);