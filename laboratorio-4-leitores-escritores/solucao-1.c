#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

sem_t sem_dados;

void* leitor(void* arg) {
    sem_wait(&sem_dados);   
    printf("Leitor %ld: lendo dados\n", (long)arg);
    sleep(1); 
    sem_post(&sem_dados); 
    return NULL;
}

void* escritor(void* arg) {
    sem_wait(&sem_dados);   
    printf("Escritor %ld: escrevendo dados\n", (long)arg);
    sleep(1); 
    sem_post(&sem_dados);  
    return NULL;
}

int main() {
    srand(time(NULL)); 

    int writers = rand() % 5 + 1; 
    int readers = rand() % 5 + 1; 

    printf("Número de escritores: %d\n", writers);
    printf("Número de leitores: %d\n", readers);

    pthread_t t_writers[writers];
    pthread_t t_readers[readers];

    sem_init(&sem_dados, 0, 1);

    for (int i = 0; i < writers; ++i) {
        pthread_create(&t_writers[i], NULL, escritor, (void*)(long)i);
    }

    for (int i = 0; i < readers; ++i) {
        pthread_create(&t_readers[i], NULL, leitor, (void*)(long)i);
    }

    for (int i = 0; i < writers; ++i) {
        pthread_join(t_writers[i], NULL);
    }

    for (int i = 0; i < readers; ++i) {
        pthread_join(t_readers[i], NULL);
    }

    sem_destroy(&sem_dados);
    return 0;
}
