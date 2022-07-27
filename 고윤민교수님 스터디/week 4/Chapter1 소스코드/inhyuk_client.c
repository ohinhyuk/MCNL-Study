#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv){
	int clnt_sock;
	//int serv_sock;

	//struct sockaddr_in clnt_adr;
	struct sockaddr_in serv_adr;
	int sz = sizeof(serv_adr);

	clnt_sock = socket(PF_INET, SOCK_STREAM , 0);
	if(clnt_sock == -1) exit(-1);

	memset(&serv_adr , 0 , sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_port = htons(atoi(argv[2]));
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

	char buf[1024];
	if(connect(clnt_sock , (struct sockaddr*) &serv_adr,sz) == -1) exit(-1);	
	int str_len;
	str_len=read(clnt_sock , &buf , sizeof(buf));
	if(str_len == 0 ) exit(-1);
	printf("%s" , buf);
	
	close(clnt_sock);
}

