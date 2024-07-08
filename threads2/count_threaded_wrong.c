#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	
	// Identifier für die Threads
	pthread_t up_t;
	pthread_t down_t;

	// Threads starten
	pthread_create(&up_t, NULL, count_up, NULL);
	pthread_create(&down_t, NULL, count_down, NULL);

	// Auf Beendigung der Threads warten
	pthread_join(up_t, NULL);
	pthread_join(down_t, NULL);

	printf("counter: %d\n",counter);
	return 0;
}
