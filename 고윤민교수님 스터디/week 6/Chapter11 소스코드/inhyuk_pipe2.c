#include <stdio.h>
#include <unistd.h>

int main(int argc , char** argv){
	int fds1[2], fds2[2];
	char str1[] = "Who are you?";
	char str2[] = "Thank you";
	char buf[1024];
	pid_t pid;

	pipe(fds1);
	pipe(fds2);
	pid = fork();

	if(pid==0)
	{
		//printf("2\n");
		write(fds1[1],str1,sizeof(str1));
		printf("1\n");
		read(fds2[0] , buf, 1024);
		//printf("Child proc output %s \n" , buf);
		printf("4\n");
	}

	else{
		//printf("1\n");
		read(fds1[0],buf,1024);
		//printf("parent proc output %s" , buf);
		printf("2\n");
		
		write(fds2[1],str2 , sizeof(str2));
		sleep(1);
		printf("3\n");
		sleep(1);
	}
	return 0;
}
