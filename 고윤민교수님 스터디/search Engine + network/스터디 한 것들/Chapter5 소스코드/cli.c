#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char** argv){
	int clnt_sock;
	int serv_sock;

	struct sockaddr_in serv_addr;

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr =inet_addr(argv[1]);

	clnt_sock = socket(PF_INET , SOCK_STREAM , 0);

	connect(clnt_sock , (struct sockaddr*)&serv_addr , sizeof(serv_addr));

	while(1){
		int str_len = 0;
		int recv_len=0, recv_cnt = 0;
		char massage[1024]= "";
	//while(getchar() != '\n');
		
		fgets(massage,sizeof(massage),stdin);

		if(!strcmp(massage,"q\n") || !strcmp(massage, "Q\n")) return 0;
		str_len = write(clnt_sock , massage , strlen(massage));
		while(str_len > recv_len){
			recv_cnt = read(clnt_sock , &massage , 1023 );
			recv_len += recv_cnt; 
		}
		massage[recv_len]=0;
		printf("%s\n" , massage);

	}
	close(clnt_sock);
}
