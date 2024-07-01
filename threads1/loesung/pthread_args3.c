#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct _funcargs{
	int x;
	int y;
} funcargs;

void* my_function(void* args){
	funcargs *fargs = (funcargs*)args;
	unsigned int *result = malloc(sizeof(unsigned int));
	*result = 0;
	for (int x = 0; x < fargs->x; x++) {
		for (int y = 0; y < fargs->y; y++) {
			*result += x*y;
			printf("x*y=%d\n",x*y);
		}
	}
	return result;
}

int main(int argc, char *argv[]){
	pthread_t my_process;
	int reps = 20;
	funcargs fargs = {.x= 5, .y=4};	
	unsigned int * result;

	pthread_create(&my_process, NULL, my_function, &fargs);

	pthread_join(my_process, (void**)&result);
	printf("Result: %u\n",*result);

	free(result);
	
	return 0;
}
