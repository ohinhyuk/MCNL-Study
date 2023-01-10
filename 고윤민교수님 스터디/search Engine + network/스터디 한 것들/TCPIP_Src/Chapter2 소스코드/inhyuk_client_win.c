#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main(int argc , char** argv){

    WSADATA wsaData;
    SOCKET serv_sock;
    SOCKET clnt_sock;

    char massage[1024];

    SOCKADDR_IN clnt_addr , serv_addr;

    if(WSAStartup(MAKEWORD(2,2) , &wsaData) != 0 ) exit(-1);

    clnt_sock = socket(PF_INET , SOCK_STREAM , 0);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if( connect(clnt_sock , (SOCKADDR*) &serv_addr , sizeof(serv_addr)) == SOCKET_ERROR) exit(-1);

    int readLen= 0 , idx = 0;
    int strLen = 0;
    while(readLen = recv(clnt_sock , &massage[idx++] ,1 , 0 ))
    {
        if(readLen==-1) exit(1);

        strLen+=readLen;

    }

    printf("%s",massage);
    printf("%d",strLen);

    closesocket(clnt_sock);
    WSACleanup();
    return 0;

}