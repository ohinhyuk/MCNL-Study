#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	
	int status;
	pid_t pid = fork();

	if(pid ==0){
		sleep(3);
		printf("Hello i'm child");
		exit(3);
	}
	else{
		while(!waitpid(-1, &status, WNOHANG)){
			printf("waiting...\n");
			sleep(1);
		}
		if(WIFEXITED(status)) printf("Child send %d\n" , WEXITSTATUS(status));
		return 0;
	}
}
