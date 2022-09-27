#include "ChatClient.h"

//-----------------------------------------------------------------------------
//      ������ �ʱ�ȭ
//-----------------------------------------------------------------------------
BOOL WINAPI SocketInit(WSADATA* lpWSAD)
{
    BOOL Rslt = FALSE;
    WSADATA WSAD;

    if (lpWSAD == NULL) lpWSAD = &WSAD;
    if (WSAStartup(MAKEWORD(2, 2), lpWSAD) != 0) goto DispErr;
    if (lpWSAD->wVersion != 0x0202)       //WS_32.DLL �����˻�
    {
        WSACleanup();

    DispErr:
        printf("���϶��̺귯���� �ʱ�ȭ �� �� �����ϴ�.");
        goto ProcExit;
    }
    Rslt++;

ProcExit:
    return Rslt;
}



//-----------------------------------------------------------------------------
//      Port�� ������ (IP�� ���ε��, ��Ʈ�� ��Ʋ�ε��)
//-----------------------------------------------------------------------------
int WINAPI MyConnect(SOCKET hSocket, LPCSTR IP, WORD PortNo)
{
    SOCKADDR_IN SA;

    ZeroMemory(&SA, sizeof(SOCKADDR_IN));
    SA.sin_family = AF_INET;
    SA.sin_port = htons(PortNo);
    SA.sin_addr.s_addr = inet_addr(PEERCHATIP);
    return connect(hSocket, (SOCKADDR*)&SA, sizeof(SA));
}



//-----------------------------------------------------------------------------
//      �ܼ� ��Ǯ ����
//-----------------------------------------------------------------------------
int main()
{
    SOCKET hSocket = INVALID_SOCKET;
    CHAR Buff[256] = { 0, };

    printf("ä�� Ŭ���̾�Ʈ ���α׷�\n");

    SocketInit(NULL);

    if ((hSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("socket() ����: %d\n", WSAGetLastError());
        goto ProcExit;
    }

    if (MyConnect(hSocket, PEERCHATIP, MYCHATPORTNO) == SOCKET_ERROR)
    {
        printf("MyConnect(%s, %d) ����: %d\n", PEERCHATIP, MYCHATPORTNO, WSAGetLastError());
        goto ProcExit;
    }

    for (;;)
    {
        printf("My> ");
        //gets(Buff);
        gets_s(Buff, sizeof(Buff));
        if (lstrcmpi(Buff, "exit") == 0) break;
        send(hSocket, Buff, lstrlen(Buff) + 1, 0);
        recv(hSocket, Buff, sizeof(Buff), 0);
        printf("Peer> %s\n", Buff);
    }

ProcExit:
    if (hSocket != INVALID_SOCKET) closesocket(hSocket);
    WSACleanup();
    return 0;
}

