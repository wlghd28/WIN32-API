#pragma once
#include "resource.h"


// �Լ� ����
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK MainDialog_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitMainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_MainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_MainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);