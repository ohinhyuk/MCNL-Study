#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFSIZE 1024

int main(int argc, char ** argv){
	int serv_sock , clnt_sock;
	FILE * readfp;
	FILE* writefp;
	char buf[BUFSIZE];
	struct sockaddr_in serv_addr , clnt_addr;

	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	serv_sock = socket(PF_INET , SOCK_STREAM , 0);
	
	bind(serv_sock , (struct sockaddr*) &serv_addr , sizeof(serv_addr));

	listen(serv_sock , 5);

	int adr_sz = sizeof(clnt_addr);

	clnt_sock = accept( serv_sock, (struct sockaddr*) &clnt_addr, &adr_sz);

	readfp = fdopen(clnt_sock , "r");
	writefp = fdopen(clnt_sock , "w");

	fputs( "From SERVER : Hi ~?\n" , writefp);
	fputs("I love all the world \n", writefp);
	fputs("U R awesome\n", writefp);
	fflush(writefp);

	fclose(writefp);
	fgets(buf , sizeof(buf) , readfp); fputs(buf,stdout);
	fclose(readfp);
	return 0;



}
