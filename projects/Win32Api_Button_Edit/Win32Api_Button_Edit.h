#pragma once

#include "resource.h"

// C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//#include <Shlwapi.h>	// wvnsprintf()
#include <strsafe.h>    // StringCbPrintf()



// �Լ� ����
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);