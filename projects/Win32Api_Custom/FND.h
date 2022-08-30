#pragma once
#include "resource.h"
#include "Bitmap.h"

#define SSM_SETVALUE    (WM_USER+0)     //wPrm: 설정할 숫자
#define SSM_GETVALUE    (WM_USER+1)

// extern 윈도우 핸들 >> Win32Api_Custom.cpp 에서 초기화가 된다.
extern HINSTANCE hInst;

struct SEVENSEGMENT_CTX
{
    HBITMAP hBtmBkgnd;
    HBITMAP hBtm7Seg;
    int DigitWidth;
    int DigitHeight;
    int Value;
};

// 함수 선언
void WINAPI Regist7Segment();

static void WINAPI DrawSevenSegment(HWND hWnd, HDC hDC, SEVENSEGMENT_CTX* SSC);

static LRESULT CALLBACK SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);