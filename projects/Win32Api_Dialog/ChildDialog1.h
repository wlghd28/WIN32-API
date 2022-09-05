#pragma once
#include "resource.h"


// 함수선언

INT_PTR CALLBACK ChildDialog1_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_ChildDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


VOID Printf_Child1(LPCSTR FormStr, ...);
BOOL WINAPI CheckDuplicateName(HWND hWnd, LPCSTR ToFileStr);
VOID WINAPI LV_InsertColumn(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align);
int WINAPI LV_InsertItem(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData);
int WINAPI LV_GetItemCount(HWND hWnd, int LVID);
VOID WINAPI LV_SetItemText(HWND hWnd, int LVID, int Row, int Column, LPCSTR DataStr);
int WINAPI LV_GetSelected(HWND hWnd, int LVID, int StartItemNo);
BOOL WINAPI LV_DeleteItem(HWND hWnd, int LVID, int DelItemNo);
int WINAPI CB_AddString(HWND hWnd, int CBID, LPCSTR ToAddStr);