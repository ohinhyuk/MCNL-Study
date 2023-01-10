#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char * message){
	fputs(message , stderr);
	fputc('\n' , stderr);
	exit(1);
}

int main(int argc, char** argv){
	
	int serv_sock;
	int clnt_sock;
	int read_cnt;

	char filename[BUF_SIZE];
	socklen_t clnt_addr_sz;

	serv_sock = socket(PF_INET , SOCK_STREAM , 0);
	if(serv_sock == -1) error_handling("sock() error");
	
	struct sockaddr_in serv_addr , clnt_addr;
	
	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(serv_sock , (struct sockaddr*) &serv_addr , sizeof(serv_addr))) error_handling("bind() error");

	if(listen(serv_sock , 5) == -1) error_handling("listen() error");
	
	
	//while(1){
		clnt_addr_sz = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock , (struct sockaddr*)&clnt_addr ,&clnt_addr_sz);
		read_cnt = read(clnt_sock , filename , BUF_SIZE - 1);
		
		write(clnt_sock , filename , read_cnt);
	close(serv_sock);
	close(clnt_sock);	
	//} 

}
