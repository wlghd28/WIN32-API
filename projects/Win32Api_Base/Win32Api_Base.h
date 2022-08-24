#pragma once

//// Win32Api_Base.h

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <Windows.h>
// C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>    // wvnsprintf()


// �Լ�����
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hInstPrev,LPSTR CmdPrm,int CmdShow);
void Printf(LPCSTR FormStr, ...);   // ��ũ�� ����� �Լ� (��������)
static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);
static void WINAPI DrawAll(HWND hWnd, HDC hDC);
static void WINAPI DrawDrag(HWND hWnd, COLORREF Col);
void WINAPI DragStart(HWND hWnd, LPARAM lPrm);
void WINAPI DragFinish(HWND hWnd, LPARAM lPrm);
void WINAPI DragMoving(HWND hWnd, LPARAM lPrm);