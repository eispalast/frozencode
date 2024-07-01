#include <stdio.h>
#include <pthread.h>

void* my_function(void* args){
	for (int i = 0; i < 10; i++) {
		printf("i=%d\n",i);
	}
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t my_process;
	
	pthread_create(&my_process, NULL, my_function, NULL);

	for (int i = 0; i < 10; i++) {
		printf("main i= %d\n",i);
	}
	pthread_join(my_process, NULL);
	
	return 0;
}
