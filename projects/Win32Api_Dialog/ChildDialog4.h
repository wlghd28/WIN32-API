#pragma once
#include "resource.h"

// �Լ�����
INT_PTR CALLBACK ChildDialog4_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitChildDialog4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_ChildDialog4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_ChildDialog4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);