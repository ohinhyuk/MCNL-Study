#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

#define BUF_SIZE 1024

void error_handling(char * message);
int main(int argc , char ** argv){
	
	// sock_servets
	
	int sock_serv;
	int clnt_sock;

	char buf[1024];
	int numsize;
	char operand;
	
	// sock_servaddr_in
	struct sockaddr_in sock_adr;
	struct sockaddr_in clnt_adr;
	
	// sock_serv_serv
	sock_serv = socket(PF_INET, SOCK_STREAM , 0);
	if(sock_serv == -1){
		error_handling("sock_serv() error");
	}

	// sock_adr setting
	memset(&sock_adr , 0 ,sizeof(sock_adr));
	sock_adr.sin_family = AF_INET;
	sock_adr.sin_port = htons(atoi(argv[1]));
	sock_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sock_serv, (struct sockaddr*)&sock_adr , sizeof(sock_adr)) == -1){
		error_handling("bind() error");
	}
	
	if(listen(sock_serv , 5) == -1){
		error_handling("listen() error");
	}
	socklen_t clnt_adr_sz = sizeof(clnt_adr);

	for(int j = 0 ; j < 5; ++j)
	{
	clnt_sock=accept(sock_serv , (struct sockaddr*)&clnt_adr , &clnt_adr_sz);
	if(clnt_sock == -1){error_handling("accept() error");}	

	// After connected
	printf("Connected...........\n");
	

	int str_len;
	
	str_len=read(clnt_sock, &buf , BUF_SIZE);
	int index = 0;

	numsize = buf[index]-'0';
	index++;
	int num[numsize];

	for(int i = 0 ; i < numsize ;++i){
	       	 num[i] = buf[index];
		 index += 4;
	}
	
	operand = buf[index];
	for(int i = 1 ; i < numsize ; ++i){
		if(operand=='+'){
			num[0] += num[i];
		}
		else if(operand=='-'){
			num[0] -= num[i];
		}
		else if(operand=='*'){
			num[0] *= num[i];
		}
		else{
			num[0] /= num[i];
		}
		printf("d : %d\n",num[0]);
	}
	
	write(clnt_sock,&num[0],sizeof(num[0]));
	
	}
	
	close(sock_serv);
	close(clnt_sock);

}

void error_handling(char * message){
	fputs(message,stderr);
	fputc('\n', stderr);
	exit(1);
}

