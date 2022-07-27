#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(int argc, char** argv){
	
	int sock;
	int clnt_sock;

	sock = socket(PF_INET, SOCK_STREAM,0);

	struct sockaddr_in sock_addr, clnt_addr;

	memset(&sock_addr , 0 , sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(atoi(argv[1]));
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sock , (struct sockaddr*) &sock_addr, sizeof(sock_addr));

	listen(sock , 5);

	socklen_t sz = sizeof(clnt_addr);

	char massage[1024];
	int str_len = 0;

	for(int i = 0 ; i < 5 ; ++i){
		clnt_sock=accept(sock ,(struct sockaddr*) &clnt_addr , &sz);
		printf("Debug");

		while( (str_len = read(clnt_sock , &massage , 1023 )) != 0 ){ write(clnt_sock , massage , str_len);
			}
			
			close(clnt_sock);
	
	}
close(sock);
	return 0;


}
