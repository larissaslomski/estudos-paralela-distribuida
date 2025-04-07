#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREADS 40

long var_compartilhada = 0;
sem_t semaforo;

void *threadSoma(void *arg) {
    int a, b;
    for(long j = 0; j < 100000; j++){
        sem_wait(&semaforo);
        a = var_compartilhada;
        b = 1;
        var_compartilhada = a + b;
        sem_post(&semaforo);
    }
}

int main(int argc, char *argv[]) {
    pthread_t t[THREADS];
    int s;
    sem_init(&semaforo, 0, 1);

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_create(&t[i], NULL, threadSoma, NULL);
    }

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_join(t[i], NULL);
    }

    printf("variavel compartilhada = %ld\n", var_compartilhada);
}