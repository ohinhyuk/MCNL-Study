#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc , char ** argv){
	int serv_sock;
	int clnt_sock;
	int str_len;

	char message[BUFSIZE];

	struct sockaddr_in serv_addr , from_addr;

	memset(&serv_addr , 0 , sizeof(serv_sock));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	clnt_sock = socket(PF_INET , SOCK_DGRAM , 0);

	while(1){
		fputs( "Insert message(q to quit): " , stdout);
		fgets( message , sizeof(message), stdin);
		if(!strcmp(message , "q\n") || !strcmp(message, "Q\n"))
			break;
		sendto(clnt_sock , message , strlen(message) , 0 , (struct sockaddr*)&serv_addr , sizeof(serv_addr));
		socklen_t adr_sz = sizeof(from_addr);
		str_len = recvfrom(clnt_sock , message , BUFSIZE , 0 , (struct sockaddr*)&from_addr , &adr_sz);
		message[str_len] = 0;
		printf("Message from server: %s" , message);
	}
}
