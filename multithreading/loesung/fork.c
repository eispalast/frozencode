#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	
	pid_t pid = fork();
	if(pid == 0){
		sleep(3);
		printf("Ich bin ein Kind-Prozess\n");
		exit(0);
	}

	else{
		printf("Ich bin ein Elternprozess\n");
		while((waitpid(pid,0,WNOHANG))==0){
			printf("Noch nicht fertig\n");
			sleep(1);
		}

	}
	printf("Das führen wir beide aus.\n");
	
	return 0;
}
