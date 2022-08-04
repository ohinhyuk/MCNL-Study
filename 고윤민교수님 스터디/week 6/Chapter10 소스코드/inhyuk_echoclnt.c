#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 30

void error_handling(char * message);
void write_routine(int sock , char* buf);
void read_routine(int sock , char * buf);
int main(int argc , char** argv){
	
	int sock;
	pid_t pid;
	char buf[BUFSIZE];
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET , SOCK_STREAM , 0);
	if(sock == -1) error_handling("sock() error");

	memset(&serv_addr, 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	if(connect(sock , (struct sockaddr*)&serv_addr , sizeof(serv_addr))==-1)		error_handling("connect() error!");

	pid = fork();
	if(pid == 0)
		write_routine(sock , buf);
	else
		read_routine(sock , buf);
	close(sock);
	return 0;
}

void read_routine(int sock , char* buf)
{
	while(1)
	{
		int str_len = read(sock , buf , BUFSIZE);
		if(str_len == 0)
			return;
		buf[str_len] = 0;
		printf("Message from server: %s" , buf);
	}
}

void write_routine(int sock , char* buf)
{
	while(1)
	{
		fgets(buf , BUFSIZE , stdin);
		if(!strcmp(buf,"q\n") || !strcmp(buf,"Q\n")){
			shutdown(sock , SHUT_WR);
			return;
		}
		write(sock , buf, strlen(buf));
	}
}

void error_handling(char* message){
	fputs(message , stderr);
	fputc('\n' , stderr);
	exit(1);
}
