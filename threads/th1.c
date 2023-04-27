#include <stdio.h>
#include <pthread.h>

pthread_t tid1,tid2;

void * p1 () {
  int i ;
  printf("thread p1 (%d) iniciando\n", getpid());
  pthread_join(tid2,NULL);
  printf("Thread 2 finished\n");
}


void * p2 () {
  int i;
  printf("thread p2 (%d) iniciando\n", getpid());
  getchar();
}

int main() {
  int result;

  printf("Main process PID (%d) \n", getpid());
  
  result = pthread_create(&tid1, NULL, p1, NULL);
  result = pthread_create(&tid2, NULL, p2, NULL);
  
  pthread_join(tid1,NULL);
  printf("Thread 1 finished\n");

  return 0;
}
