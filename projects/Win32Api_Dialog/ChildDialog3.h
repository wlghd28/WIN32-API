#pragma once
#include "resource.h"

// �Լ� ����
INT_PTR CALLBACK ChildDialog3_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI InitChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void WINAPI WM_CmdProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void WINAPI WM_NotifyProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);