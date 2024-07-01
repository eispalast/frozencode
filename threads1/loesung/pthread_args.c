#include <stdio.h>
#include <pthread.h>

void* my_function(void* args){
	int reps = *(int*)args;
	for (int i = 0; i < reps; i++) {
		printf("i=%d\n",i);
	}
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t my_process;
	int reps = 20;
	
	pthread_create(&my_process, NULL, my_function, &reps);

	pthread_join(my_process, NULL);
	
	return 0;
}
