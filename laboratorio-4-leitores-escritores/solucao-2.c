#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//permitir varios leitores 

#include <semaphore.h>

sem_t mutex, writeblock;
int data;
sem_init(&mutex, 0, 1);
sem_init(&writeblock, 0, 1);
int rcount = 0;

void *reader(void *arg){
    int f = ((int)arg);
    sem_wait(&mutex);
    rcount= rcount+ 1;
    if(rcount==1)
        sem_wait(&writeblock);
    sem_post(&mutex);
    printf("Reader %d read %d\n", f, data);
    sem_wait(&mutex);
    rcount= rcount-1;
    if(rcount==0)
    sem_post(&writeblock);
    sem_post(&mutex);
}

void *writer(void *arg){
 int f = ((int) arg);
 sem_wait(&writeblock);
 data++;
 printf("Writer %d wrote %d\n", f, data);
 sem_post(&writeblock);
}