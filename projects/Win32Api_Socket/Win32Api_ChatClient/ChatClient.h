#pragma once
#pragma warning(disable:4996)		//���ȿ� ����ϴٴ� �ܼҸ��� ����
#pragma comment(lib,"Ws2_32.lib")	//winsock2 ���̺귯�� ����
#define  WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <stdio.h>

#define PEERCHATIP      "127.0.0.1"
#define MYCHATPORTNO    10000


// �Լ� ����
BOOL WINAPI SocketInit(WSADATA* lpWSAD);
int WINAPI MyConnect(SOCKET hSocket, LPCSTR IP, WORD PortNo);