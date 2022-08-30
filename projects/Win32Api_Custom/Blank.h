#pragma once
#include "resource.h"
#include "Bitmap.h"


#define BLM_UPDATE 501

// extern 윈도우 핸들 >> Win32Api_Custom.cpp 에서 초기화가 된다.
extern HINSTANCE hInst;

struct BLANK
{
    HBITMAP hBtmBkgnd;
    HBITMAP hBtmBlank;
    int DigitWidth;
    int DigitHeight;
};



// 함수 선언
void WINAPI RegistBlank();

static void WINAPI DrawBlank(HWND hWnd, HDC hDC, BLANK* BLK);

static LRESULT CALLBACK BlankWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);