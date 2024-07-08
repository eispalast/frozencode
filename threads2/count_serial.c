#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP_TIME 50 //µsec
#define ITERATIONS 10000

int counter;

void* count_up(void* args){
	for (size_t i = 0; i < ITERATIONS; i++) {
		usleep(SLEEP_TIME);
		counter++;
	}
	return NULL;	
}

void* count_down(void* args){
	for (size_t i = 0; i < ITERATIONS; i++) {
		usleep(SLEEP_TIME);
		counter--;
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
