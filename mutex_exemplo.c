#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 40

long var_compartilhada = 0;

pthread_mutex_t mutex;

void *threadSoma(void *arg) {
    int a, b;
    for(long j = 0; j < 100000; j++){
        pthread_mutex_lock(&mutex);
        a = var_compartilhada;
        b = 1;
        var_compartilhada = a + b;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[]) {
    pthread_t t[THREADS];
    int s;

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_create(&t[i], NULL, threadSoma, NULL);
    }

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_join(t[i], NULL);
    }

    printf("variavel compartilhada = %ld\n", var_compartilhada);
}