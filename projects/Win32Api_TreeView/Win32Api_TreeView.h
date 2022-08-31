#pragma once

#include "resource.h"

#include <Commctrl.h>   //TreeView

// 함수 선언
void FileList(HWND hWnd, HTREEITEM htr, char* path);

void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);

void WINAPI InitTreeView(HWND hWnd);

static VOID WINAPI DrawAll(HWND hWnd, HDC hDC);

HTREEITEM WINAPI TV_InsertItem(HWND hWnd, int TVID, HTREEITEM hParent, HTREEITEM hInsAfter, LPCSTR Str, LPARAM lPrm);

BOOL WINAPI TV_DeleteItem(HWND hWnd, int TVID, HTREEITEM hItem);

HTREEITEM WINAPI TV_GetCurSel(HWND hWnd, int TVID);
