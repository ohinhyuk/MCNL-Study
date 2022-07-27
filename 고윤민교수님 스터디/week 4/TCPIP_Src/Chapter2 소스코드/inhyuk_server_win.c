#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main(int argc , char** argv){

    SOCKET hservSock;
    SOCKET clnt_SOCK;
    SOCKADDR_IN sock_addr;

    char massage[] = "Hello world";

    WSADATA wsaData;

    if(WSAStartup( MAKEWORD(2,2) , &wsaData) != 0 ) exit(-1);

    hservSock = socket(PF_INET , SOCK_STREAM , 0);
    if(hservSock == INVALID_SOCKET) exit(-1);

    memset(&sock_addr , 0 , sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(argv[1])); 
    sock_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(hservSock , (SOCKADDR*)&sock_addr , sizeof(sock_addr)) ==SOCKET_ERROR) exit(-1);

    if(listen(hservSock , 5) == SOCKET_ERROR) exit(-1);

    SOCKADDR_IN clnt_addr;
    int sz = sizeof(clnt_addr);

    clnt_SOCK = accept(hservSock , (SOCKADDR*)&clnt_addr , &sz);
    if(clnt_SOCK == INVALID_SOCKET) exit(-1);

    send(clnt_SOCK,massage , sizeof(massage),0);
    closesocket(clnt_SOCK);
    closesocket(hservSock);
    WSACleanup();
    return 0;

}