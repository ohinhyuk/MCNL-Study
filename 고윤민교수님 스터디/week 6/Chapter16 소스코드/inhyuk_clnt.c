#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 1024

int main(int argc, char ** argv){
	int sock;
	char buf[BUFSIZE];
	struct sockaddr_in serv_addr;

	FILE* readfp;
	FILE* writefp;

	if( (sock = socket(PF_INET , SOCK_STREAM , 0 ) ) == -1)
		exit(1);

	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	connect(sock , (struct sockaddr *) &serv_addr , sizeof(serv_addr));

	readfp = fdopen( sock , "r");
	writefp = fdopen( sock , "w");

	while(1){
		if(fgets(buf, sizeof(buf) ,readfp) == NULL)
			break;
		fputs( buf , stdout );
		fflush(readfp);

	}

	fputs("FROM CLIENT : Thank you\n" , writefp);
	fflush(writefp);
	fclose(writefp); fclose(readfp);
	return 0;

}
