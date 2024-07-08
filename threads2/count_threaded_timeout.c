#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#define SLEEP_TIME 50 //µsec
#define ITERATIONS 10000

pthread_mutex_t mutex;
pthread_cond_t signal;

int counter;

void* count_up(void* args){
	for (size_t i = 0; i < ITERATIONS; i++) {
		usleep(SLEEP_TIME);
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_cond_signal(&signal);
		pthread_mutex_unlock(&mutex);
	}
	printf("Countup fertig\n");
	return NULL;	
}

void* count_down(void* args){
	while (1) {
		usleep(SLEEP_TIME);
		pthread_mutex_lock(&mutex);
		while(counter<5){
			// printf("%d\n",counter);
			struct timespec ts;
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec+=1;
			int timeout = pthread_cond_timedwait(&signal, &mutex, &ts);
			if(timeout == ETIMEDOUT){
				printf("timeout\n");
				pthread_exit(NULL);
			}
			else{
				printf("got signal\n");
			}
		}
		counter-=5;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;	
}


int main(int argc, char *argv[]){
	
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&signal, NULL);
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
