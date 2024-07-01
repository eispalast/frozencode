#include <stdio.h>
#include <pthread.h>

typedef struct _funcargs{
	int x;
	int y;
} funcargs;

void* my_function(void* args){
	funcargs *fargs = (funcargs*)args;
	for (int x = 0; x < fargs->x; x++) {
		for (int y = 0; y < fargs->y; y++) {
			printf("x*y=%d\n",x*y);
		}
	}
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t my_process;
	int reps = 20;
	funcargs fargs = {.x= 20, .y=15};	

	pthread_create(&my_process, NULL, my_function, &fargs);

	pthread_join(my_process, NULL);
	
	return 0;
}
