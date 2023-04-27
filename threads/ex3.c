#define NUM_THREADS 10

#include <pthread.h>
#include <stdio.h>

void *PrintHello(void *threadid){
	int tid;

	tid = (int)(long int)threadid;
	printf("Hello World! It's me, thread #%d!\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	long int rc, t;

	for(t=0; t<NUM_THREADS; t++){
		printf("In main: creating thread %ld\n", (long)t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)(long)t);
		if (rc){
			printf("ERROR code is %ld\n", (long)rc);
			return -1;
		}
	}
	pthread_exit(NULL);
}

