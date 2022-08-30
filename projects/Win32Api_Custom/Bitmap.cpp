#include "framework.h"
#include "Bitmap.h"

//-----------------------------------------------------------------------------
//          비트맵 파일을 로딩함
//-----------------------------------------------------------------------------
HBITMAP WINAPI LoadBitmapFile(LPCSTR FileName)
{
    return (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}



//-----------------------------------------------------------------------------
//       hBitmap을 그림
//-----------------------------------------------------------------------------
void WINAPI DrawBitmap(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY, int CopyMode)
{
    HDC hMemDC;

    hMemDC = CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBtm);
    BitBlt(hDC, DestX, DestY, Width, Height, hMemDC, SrcX, SrcY, CopyMode);
    DeleteDC(hMemDC);
}

