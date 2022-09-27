#include "ChatServer.h"




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
int WINAPI MyBind(SOCKET hSocket, LPCSTR IP, WORD PortNo)
{
    SOCKADDR_IN SA;

    ZeroMemory(&SA, sizeof(SOCKADDR_IN));
    SA.sin_family = AF_INET;
    SA.sin_port = htons(PortNo);
    SA.sin_addr.s_addr = inet_addr(IP);
    return bind(hSocket, (SOCKADDR*)&SA, sizeof(SA));
}



//-----------------------------------------------------------------------------
//      IP�� ���ڿ��� ����� �� (inet_ntoa()�� ���� ���)
//      IPAddr�� �򿣵����
//-----------------------------------------------------------------------------
LPSTR WINAPI IPtoA(LPSTR Buff, DWORD IPAddr)
{
    wsprintf(Buff, "%d.%d.%d.%d", IPAddr & 0xFF, (IPAddr >> 8) & 0xFF, (IPAddr >> 16) & 0xFF, (IPAddr >> 24) & 0xFF); // SA.sin_addr.s_net, SA.sin_addr.s_host, SA.sin_addr.s_lh, SA.sin_addr.s_impno
    return Buff;
}



//-----------------------------------------------------------------------------
//      Accept()�� �����ϴ� �Լ�
//-----------------------------------------------------------------------------
int WINAPI MyAccept(SOCKET hSockSvr, LPSTR ConnectedIP)
{
    int Len;
    SOCKET hSockConn;
    SOCKADDR_IN SAI;

    Len = sizeof(SOCKADDR_IN);
    hSockConn = accept(hSockSvr, (SOCKADDR*)&SAI, &Len);
    if (ConnectedIP) IPtoA(ConnectedIP, SAI.sin_addr.s_addr);
    return hSockConn;
}



//-----------------------------------------------------------------------------
//      �ܼ� ��Ǯ ����
//-----------------------------------------------------------------------------
int main()
{
    int Rslt;
    SOCKET hSocket = INVALID_SOCKET;
    CHAR Buff[256], ConnectedIP[20];

    printf("ä�� ���� ���α׷�\n");

    SocketInit(NULL);

    if ((hSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("socket() �Լ� ����: %d\n", WSAGetLastError());
        goto ProcExit;
    }

    if (MyBind(hSocket, "0.0.0.0", MYCHATPORTNO) == SOCKET_ERROR)
    {
        printf("MyBind() Error %d\n", WSAGetLastError());
        goto ProcExit;
    }

    if (listen(hSocket, SOMAXCONN) == SOCKET_ERROR)   //Ŭ���̾�Ʈ�� ������ �޾Ƶ��̴� ���� Ȱ��ȭ ��Ŵ
    {
        printf("listen() Error %d\n", WSAGetLastError());
        goto ProcExit;
    }

    for (;;)
    {
        SOCKET hSocketClient;

        if ((hSocketClient = MyAccept(hSocket, ConnectedIP)) == INVALID_SOCKET)
        {
            printf("MyAccept error\n");
            continue;
        }
        printf("������: %s\n", ConnectedIP);

        for (;;)
        {
            if ((Rslt = recv(hSocketClient, Buff, sizeof(Buff), 0)) <= 0) break;    //�������� 0�� ������
            printf("Peer> %s\n", Buff);

            printf("Svr> ");
            //gets(Buff);
            gets_s(Buff, sizeof(Buff));
            if (lstrcmpi(Buff, "exit") == 0) break;
            send(hSocketClient, Buff, lstrlen(Buff) + 1, 0);
        }
        closesocket(hSocketClient);
    }

ProcExit:
    if (hSocket != INVALID_SOCKET) closesocket(hSocket);
    WSACleanup();
    return 0;
}
