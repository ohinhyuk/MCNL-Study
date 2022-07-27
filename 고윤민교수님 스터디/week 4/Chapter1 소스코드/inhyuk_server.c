#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc , char** argv){
	int sock;
	int clnt_sock;

	sock = socket(PF_INET , SOCK_STREAM, 0);
	struct sockaddr_in sock_adr;
	struct sockaddr_in clnt_adr;

	if(sock == -1) exit(-1);

	memset(&sock_adr,0,sizeof(sock_adr));
	sock_adr.sin_family = AF_INET;
	sock_adr.sin_port = htons(atoi(argv[1]));
	sock_adr.sin_addr.s_addr = htonl(INADDR_ANY);

	
	if(bind(sock, (struct sockaddr*) &sock_adr , sizeof(sock_adr) ) == -1) exit(-1);
	
	if(listen(sock , 5) == -1) exit(-1);
	
	socklen_t sz = sizeof(clnt_adr);
	clnt_sock = accept(sock, (struct sockaddr*)&clnt_adr ,&sz);
	if(clnt_sock == -1) exit(-1);
	
	char message[] = "Hello Inhyuk";
	int readlen;
	//readlen = read(clnt_sock , &buf , sizeof(buf));
	write(clnt_sock , message , sizeof(message));

	close(clnt_sock);
	close(sock);
	return 0;
}
