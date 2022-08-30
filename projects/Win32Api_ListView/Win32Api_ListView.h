#pragma once

#include "resource.h"
#include <CommCtrl.h>   //ListView

// 함수 선언
void WINAPI WM_CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI CreateControl(HWND hWnd);

BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr);

void WINAPI InitListView(HWND hWnd);

int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr);

int WINAPI LB_AddString(HWND hWnd, int LBID, LPCSTR ToAddStr);

int WINAPI LB_GetCurSel(HWND hWnd, int LBID);

int WINAPI LB_DeleteString(HWND hWnd, int LBID, int ToDelIdx);

int WINAPI LB_GetCount(HWND hWnd, int LBID);

VOID WINAPI LV_InsertColumn(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align);

int WINAPI LV_InsertItem(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData);

int WINAPI LV_GetItemCount(HWND hWnd, int LVID);

VOID WINAPI LV_SetItemText(HWND hWnd, int LVID, int Row, int Column, LPCSTR DataStr);

int WINAPI LV_GetSelected(HWND hWnd, int LVID, int StartItemNo);

BOOL WINAPI LV_DeleteItem(HWND hWnd, int LVID, int DelItemNo);