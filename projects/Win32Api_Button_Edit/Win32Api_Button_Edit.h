#pragma once

#include "resource.h"

// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//#include <Shlwapi.h>	// wvnsprintf()
#include <strsafe.h>    // StringCbPrintf()



// 함수 선언
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);