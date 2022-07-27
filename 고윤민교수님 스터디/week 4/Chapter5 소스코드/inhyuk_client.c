#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

void error_handling(char *message);

int main(int argc , char** argv){

	int sock;
	int sock_serv;
	
	char buf[1024];

	struct sockaddr_in sockserv_addr;

	sock = socket(PF_INET , SOCK_STREAM , 0);
	if(sock == -1){
		error_handling("sock() error");
	}
	memset(&sockserv_addr , 0 , sizeof(sockserv_addr));
	sockserv_addr.sin_family = AF_INET;
	sockserv_addr.sin_port = htons(atoi(argv[2]));
	sockserv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock , (struct sockaddr*)&sockserv_addr , sizeof(sockserv_addr)) == -1){
	error_handling("connect() error");
	}
	
	printf("connected");

	
		int i = 0;
		int index = 0;
		int operator_cnt;

		printf("Operand count : ");
		fflush(stdout);
		buf[index]=(char)fgetc(stdin);
		operator_cnt = buf[index++]-'0';
		//printf("%d\n", operator_cnt);
		
		for(int i = 1; i <= operator_cnt ; ++i){
			
			scanf("%d", (int*)&buf[index]);
			printf("Operand %d: %d\n",i,buf[index]);
			
			index += 4;
		}
		while(getchar()!='\n');
		//buf[index]=fgetc(stdin);
		scanf("%c",&buf[index]);
		char oper = buf[index];
		printf("Operator: %c\n",oper);
		
		while(getchar()!='\n');

		write(sock,&buf,4*operator_cnt + 2);
		int recv_cnt;
		read(sock,&recv_cnt,4);

		printf("Operation result: %d",recv_cnt);
	
	close(sock);
	close(sock_serv);


}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n' , stderr);
	exit(1);
}

