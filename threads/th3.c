#include <stdio.h>
#include <pthread.h>

pthread_t tid1,tid2;

int a = 0;
int b = 0;
int c = 0;

void * p1 () {
  int i ;
  printf("Thread p1 (%d) iniciando\n", getpid());
  for(i=0; i<1000000; i++) {
    a = a + 2 ;
//	usleep(rand()%5);
    c++;
  }
}

void * p2 () {
  int i;
  printf("Thread p2 (%d) iniciando\n", getpid());
  for (i=0; i<1000000; i++) {
	b = b + 5 ;
//	usleep(rand()%5);
	c+=2;
  }
}

int main() {
  int result;

  printf("PID do processo pai (%d) \n", getpid());  
  printf("Pai: Valor da variavel a eh %d\n", a);
  result = pthread_create(&tid1, NULL, p1, NULL);
  printf("Pai(post1): Valor da variavel a eh %d\n", a);
  printf("Pai(post1): Valor da variavel b eh %d\n", b);
  result = pthread_create(&tid2, NULL, p2, NULL);
  printf("Pai(post2): Valor da variavel a eh %d\n", a);
  printf("Pai(post2): Valor da variavel b eh %d\n", b);
  pthread_join(tid1,NULL);
  printf("Thread 1 finalizada: valor da variavel a eh %d\n", a);
  a++;
  printf("Novo valor da variavel a eh %d\n", a);
  pthread_join(tid2,NULL);
  printf("Thread 2 finalizada: valor da variavel b eh %d\n", b);
  b++;
  printf("Novo valor da variavel b eh %d\n", b);

  printf("Valor final da variavel c eh %d\n", c);
  return 0;
}
