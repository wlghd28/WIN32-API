#pragma once
#pragma warning(disable:4996)		//���ȿ� ����ϴٴ� �ܼҸ��� ����
#pragma comment(lib,"Ws2_32.lib")	// winsock2 ���̺귯�� ����
#define  WIN32_LEAN_AND_MEAN
#undef UNICODE
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>


#define MYCHATPORTNO    10000


// �Լ� ����
BOOL WINAPI SocketInit(WSADATA* lpWSAD);
int WINAPI MyBind(SOCKET hSocket, LPCSTR IP, WORD PortNo);
LPSTR WINAPI IPtoA(LPSTR Buff, DWORD IPAddr);
int WINAPI MyAccept(SOCKET hSockSvr, LPSTR ConnectedIP);
