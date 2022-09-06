#pragma once
#include "resource.h"

// 함수 선언
INT_PTR CALLBACK ChildDialog3_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


VOID Printf_Child3(LPCSTR FormStr, ...);
BOOL WINAPI CheckDuplicateName_Child3(HWND hWnd, LPCSTR ToFileStr);
VOID WINAPI LV_InsertColumn_Child3(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align);
int WINAPI LV_InsertItem_Child3(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData);
int WINAPI LV_GetItemCount_Child3(HWND hWnd, int LVID);
VOID WINAPI LV_SetItemText_Child3(HWND hWnd, int LVID, int Row, int Column, LPCSTR DataStr);
int WINAPI LV_GetSelected_Child3(HWND hWnd, int LVID, int StartItemNo);
BOOL WINAPI LV_DeleteItem_Child3(HWND hWnd, int LVID, int DelItemNo);
int WINAPI CB_AddString_Child3(HWND hWnd, int CBID, LPCSTR ToAddStr);
VOID WINAPI DrawBitmap_Child3(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY, int CopyMode);
VOID WINAPI DrawTwoColorRect_Child3(HDC hDC, RECT* R, COLORREF Col1, COLORREF Col2);
VOID WINAPI DrawOwnerButton_Child3(DRAWITEMSTRUCT* DIS, int BtmID);

