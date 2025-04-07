// compilar com gcc -pthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

void *t_function(void *arg){
    long *rank;
    rank = (long *)arg;
	printf("Thread #%ld em execucao!\n",*rank);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t t[NUM_THREADS];
  long i;
  long ids[NUM_THREADS];

  for (i = 0 ; i < NUM_THREADS; i++){
    ids[i] = i;
    printf("Ciando a thread %ld , com id %ld\n",i,ids[i]);
    pthread_create(&t[i],NULL,t_function,(void *)&ids[i]);
  }
  printf("Aguardando termino das threads\n");
  for(i=0; i < NUM_THREADS; i++)
	pthread_join(t[i],NULL);
  printf("Threads terminaram\n");
  return 0;	// pode usar tambem macros EXIT_SUCCESS
}
