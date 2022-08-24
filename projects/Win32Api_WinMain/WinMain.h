#pragma once

//// WinMain.h

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <Windows.h>
// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>    // wvnsprintf()


// 함수선언
int WINAPI WinMain
(
    HINSTANCE hInst, 
    HINSTANCE hInstPrev, 
    LPSTR CmdPrm, 
    int CmdShow
);

void Printf(LPCSTR FormStr, ...);   // 스크린 디버그 함수 (가변인자)