#pragma once
#include "resource.h"
#include "Bitmap.h"

#define SSM_SETVALUE    (WM_USER+0)     //wPrm: ������ ����
#define SSM_GETVALUE    (WM_USER+1)

// extern ������ �ڵ� >> Win32Api_Custom.cpp ���� �ʱ�ȭ�� �ȴ�.
extern HINSTANCE hInst;

struct SEVENSEGMENT_CTX
{
    HBITMAP hBtmBkgnd;
    HBITMAP hBtm7Seg;
    int DigitWidth;
    int DigitHeight;
    int Value;
};

// �Լ� ����
void WINAPI Regist7Segment();

static void WINAPI DrawSevenSegment(HWND hWnd, HDC hDC, SEVENSEGMENT_CTX* SSC);

static LRESULT CALLBACK SevenSegmentWndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm);