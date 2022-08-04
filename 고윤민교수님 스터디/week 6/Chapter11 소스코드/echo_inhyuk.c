#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

int main(int argc, char** argv){

	//sock
	int serv_sock , clnt_sock;
		
	//sock init
	serv_sock = socket(PF_INET, SOCK_STREAM , 0);
	if(serv_sock == -1) exit(1);

	//serv_sock binding
	struct sockaddr_in serv_addr , clnt_addr;
	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	
	if(bind(serv_sock , (struct sockaddr*) &serv_addr , sizeof(serv_addr)) == -1) exit(1);


	//listening
	if(listening(serv_sock , 5) == -1 ) exit(1);


	// multi process
	pid_t pid;
	pid = fork();

	// pipe
	struct sigaction act;
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	int state = sigaction(SIGCHLD , &act , 0);
	
	int fds[2];
	pipe(fds);


	if(pid==0){
		FILE * fp = fopen("echomsg.txt", "wt");
		char msgbuf[1024];
		int i , len;
		
		for(i = 0 ; i < 10 ; ++ i){
			len = read(fds[0] , mugbuf , 1024);
			fwrite((void*)msgbuf , 1 ,len , fp );
		}
		fclose(fp);
		return 0;
	}
	else{
		while(1)
		{
			int adr_sz = sizeof(clnt_addr);
			clnt_sock = accept(serv_sock , (struct sockaddr*)&clnt_addr , &adr_sz);
			if(clnt_sock == -1) continue;
			else puts("new client connected...");

			pid = fork();
			if(pid==0)
			{
				close(serv_sock);
				while((str_len = read(clet_sock , buf , 1024)))
			}
		}

	}

}
