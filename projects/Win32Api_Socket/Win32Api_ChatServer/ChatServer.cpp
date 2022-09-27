#include "ChatServer.h"




//-----------------------------------------------------------------------------
//      소켓을 초기화
//-----------------------------------------------------------------------------
BOOL WINAPI SocketInit(WSADATA* lpWSAD)
{
    BOOL Rslt = FALSE;
    WSADATA WSAD;

    if (lpWSAD == NULL) lpWSAD = &WSAD;
    if (WSAStartup(MAKEWORD(2, 2), lpWSAD) != 0) goto DispErr;
    if (lpWSAD->wVersion != 0x0202)       //WS_32.DLL 버젼검사
    {
        WSACleanup();

    DispErr:
        printf("소켓라이브러리를 초기화 할 수 없습니다.");
        goto ProcExit;
    }
    Rslt++;

ProcExit:
    return Rslt;
}



//-----------------------------------------------------------------------------
//      Port를 설정함 (IP는 빅인디언, 포트는 리틀인디언)
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
//      IP를 문자열로 만들어 줌 (inet_ntoa()와 같은 기능)
//      IPAddr은 빅엔디언임
//-----------------------------------------------------------------------------
LPSTR WINAPI IPtoA(LPSTR Buff, DWORD IPAddr)
{
    wsprintf(Buff, "%d.%d.%d.%d", IPAddr & 0xFF, (IPAddr >> 8) & 0xFF, (IPAddr >> 16) & 0xFF, (IPAddr >> 24) & 0xFF); // SA.sin_addr.s_net, SA.sin_addr.s_host, SA.sin_addr.s_lh, SA.sin_addr.s_impno
    return Buff;
}



//-----------------------------------------------------------------------------
//      Accept()를 쉽게하는 함수
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
//      콘솔 어풀 메인
//-----------------------------------------------------------------------------
int main()
{
    int Rslt;
    SOCKET hSocket = INVALID_SOCKET;
    CHAR Buff[256], ConnectedIP[20];

    printf("채팅 서버 프로그램\n");

    SocketInit(NULL);

    if ((hSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("socket() 함수 오류: %d\n", WSAGetLastError());
        goto ProcExit;
    }

    if (MyBind(hSocket, "0.0.0.0", MYCHATPORTNO) == SOCKET_ERROR)
    {
        printf("MyBind() Error %d\n", WSAGetLastError());
        goto ProcExit;
    }

    if (listen(hSocket, SOMAXCONN) == SOCKET_ERROR)   //클라이언트의 접속을 받아들이는 것을 활성화 시킴
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
        printf("접속자: %s\n", ConnectedIP);

        for (;;)
        {
            if ((Rslt = recv(hSocketClient, Buff, sizeof(Buff), 0)) <= 0) break;    //끊어지면 0을 리턴함
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
