#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

void error_handling(char * message){
	fputs(message , stderr);
	fputc('\n' , stderr);
	exit(1);
}

int main(int argc , char** argv){
	int serv_sock;
	int clnt_sock;
	char message[1024];

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	socklen_t adr_sz;

	memset(&serv_addr, 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	serv_sock = socket(PF_INET , SOCK_DGRAM,0);
	if(serv_sock == -1) error_handling("sock() error");
	
	if(bind(serv_sock , (struct sockaddr*)&serv_addr , sizeof(serv_addr) )==-1) error_handling("bind() error");
	
	while(1){
		adr_sz = sizeof(clnt_addr);
		int str_len = recvfrom(serv_sock,&message,1024,0,(struct sockaddr*) &clnt_addr , &adr_sz);
		sendto(serv_sock , message , str_len , 0 , (struct sockaddr*)&clnt_addr , adr_sz );
	}
	close(serv_sock);

	/*
	for(int i=0 ; i < 3; ++i){
		sleep(5);
		adr_sz = sizeof(clnt_addr);
		str_len = recvfrom(sock , &message ,1024,0 ,(struct sockaddr*) &clnt_addr, &adr_sz )
		printf("Message %d:  %s", i+1, message);
	}
*/
	
	
}
