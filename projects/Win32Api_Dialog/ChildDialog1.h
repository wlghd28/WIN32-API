#pragma once
#include "resource.h"


// 함수선언

INT_PTR CALLBACK ChildDialog1_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


VOID Printf_Child1(LPCSTR FormStr, ...);
BOOL WINAPI CheckDuplicateName_Child1(HWND hWnd, LPCSTR ToFileStr);
VOID WINAPI LV_InsertColumn_Child1(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align);
int WINAPI LV_InsertItem_Child1(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData);
int WINAPI LV_GetItemCount_Child1(HWND hWnd, int LVID);
VOID WINAPI LV_SetItemText_Child1(HWND hWnd, int LVID, int Row, int Column, LPCSTR DataStr);
int WINAPI LV_GetSelected_Child1(HWND hWnd, int LVID, int StartItemNo);
BOOL WINAPI LV_DeleteItem_Child1(HWND hWnd, int LVID, int DelItemNo);
int WINAPI CB_AddString_Child1(HWND hWnd, int CBID, LPCSTR ToAddStr);