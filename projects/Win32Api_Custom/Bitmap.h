#pragma once
#include "resource.h"

HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName);

void WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY, int CopyMode);