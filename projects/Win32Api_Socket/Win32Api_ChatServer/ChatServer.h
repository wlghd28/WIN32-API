#pragma once
#pragma warning(disable:4996)		//보안에 취약하다는 잔소리를 없앰
#pragma comment(lib,"Ws2_32.lib")	// winsock2 라이브러리 연결
#define  WIN32_LEAN_AND_MEAN
#undef UNICODE
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>


#define MYCHATPORTNO    10000


// 함수 선언
BOOL WINAPI SocketInit(WSADATA* lpWSAD);
int WINAPI MyBind(SOCKET hSocket, LPCSTR IP, WORD PortNo);
LPSTR WINAPI IPtoA(LPSTR Buff, DWORD IPAddr);
int WINAPI MyAccept(SOCKET hSockSvr, LPSTR ConnectedIP);
