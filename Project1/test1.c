#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#define NUM_THREADS 200

int SharedVariable = 0;

void* SimpleThread(void *args){
	long which = (long)args;
	int num, val;
	for(num = 0; num < 20; num++){
		if(random() > RAND_MAX/2)
			usleep(500);

		val = SharedVariable;
		printf("*** Thread %ld sees value %d\n", which, val);
		SharedVariable = val + 1;
	}
	val = SharedVariable = val + 1;
	printf("Thread %ld sees value %d\n", which, val);
	pthread_exit(0);
}

int main(int argc, char **argv){
	pthread_t threads[NUM_THREADS];
	long t;
	for(t = 0; t < NUM_THREADS; t++){
		printf("In main: creating thread %ld\n", t);
		pthread_create(&threads[t], NULL, SimpleThread, (void *)t);
	}

	pthread_exit(0);
}
