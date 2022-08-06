#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>

int main(){
	
	FILE *fp;

	int fd = open("data.dat" , O_WRONLY|O_CREAT|O_TRUNC);
	if(fd == -1) exit(1);

	fp = fdopen(fd , "w");

	fputs("Heelo world!!\n", fp);
	fclose(fp);
	return 0;

}
