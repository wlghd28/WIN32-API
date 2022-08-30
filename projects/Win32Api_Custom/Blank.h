#pragma once
#include "resource.h"
#include "Bitmap.h"


#define BLM_UPDATE 501

// extern ������ �ڵ� >> Win32Api_Custom.cpp ���� �ʱ�ȭ�� �ȴ�.
extern HINSTANCE hInst;

struct BLANK
{
    HBITMAP hBtmBkgnd;
    HBITMAP hBtmBlank;
    int DigitWidth;
    int DigitHeight;
};



// �Լ� ����
void WINAPI RegistBlank();

static void WINAPI DrawBlank(HWND hWnd, HDC hDC, BLANK* BLK);

static LRESULT CALLBACK BlankWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);