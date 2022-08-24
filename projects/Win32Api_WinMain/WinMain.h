#pragma once

//// WinMain.h

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
int WINAPI WinMain
(
    HINSTANCE hInst, 
    HINSTANCE hInstPrev, 
    LPSTR CmdPrm, 
    int CmdShow
);

void Printf(LPCSTR FormStr, ...);   // ��ũ�� ����� �Լ� (��������)