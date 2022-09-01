#pragma once

#include "resource.h"

#include <Commctrl.h>   //TreeView

// 함수 선언
void FileList(HWND hWnd, HTREEITEM htr, char* path);

void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_NotifyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);

void WINAPI InitTreeView(HWND hWnd);

static VOID WINAPI DrawAll(HWND hWnd, HDC hDC);

HTREEITEM WINAPI TV_InsertItem(HWND hWnd, int TVID, HTREEITEM hParent, HTREEITEM hInsAfter, LPCSTR Str, LPARAM lPrm);

BOOL WINAPI TV_DeleteItem(HWND hWnd, int TVID, HTREEITEM hItem);

BOOL WINAPI TV_DeleteAllChildItem(HWND hWnd, int TVID, HTREEITEM hItem);

HTREEITEM WINAPI TV_GetCurSel(HWND hWnd, int TVID);

HTREEITEM WINAPI TV_GetParentCurSel(HWND hWnd, int TVID, HTREEITEM htr);

HTREEITEM WINAPI TV_GetChildCurSel(HWND hWnd, int TVID, HTREEITEM htr);

TVITEM WINAPI TV_GetItemInfo(HWND hWnd, int TVID, HTREEITEM htr);

void WINAPI TV_GetItemPath(HWND hWnd, int TVID, HTREEITEM htr, char* path);