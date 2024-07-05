#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP_TIME 100 //µsec
#define ITERATIONS 10000

int counter;

void* count_up(void* args){
	for (size_t i = 0; i < ITERATIONS; i++) {
		counter++;
		usleep(SLEEP_TIME);
	}
	return NULL;	
}

void* count_down(void* args){
	for (size_t i = 0; i < ITERATIONS; i++) {
		counter--;
		usleep(SLEEP_TIME);
	}
	return NULL;	
}


int main(int argc, char *argv[]){
	counter = 0;
	count_up(NULL);
	count_down(NULL);

	printf("counter: %d\n",counter);
	return 0;
}
