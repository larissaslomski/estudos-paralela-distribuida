#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_TASKS 10
#define NUM_THREADS 4

// Estrutura de uma tarefa
typedef struct {
    int number;
} Task;

// Fila circular de tarefas
Task task_queue[MAX_TASKS];
int queue_start = 0, queue_end = 0, task_count = 0;

// Sincronização
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

// Adiciona tarefa na fila
void enqueue(Task task) {
    pthread_mutex_lock(&mutex);
    while (task_count == MAX_TASKS)
        pthread_cond_wait(&not_full, &mutex);

    task_queue[queue_end] = task;
    queue_end = (queue_end + 1) % MAX_TASKS;
    task_count++;

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}

// Retira tarefa da fila
Task dequeue() {
    pthread_mutex_lock(&mutex);
    while (task_count == 0)
        pthread_cond_wait(&not_empty, &mutex);

    Task task = task_queue[queue_start];
    queue_start = (queue_start + 1) % MAX_TASKS;
    task_count--;

    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);

    return task;
}

// Função executada pelas threads consumidoras
void* worker(void* arg) {
    while (1) {
        Task task = dequeue();
        printf("Thread %ld: processando número %d -> quadrado = %d\n",
               (long)pthread_self(), task.number, task.number * task.number);
        sleep(1); // Simula tempo de processamento
    }
    return NULL;
}

// Função do produtor
void* producer(void* arg) {
    for (int i = 1; i <= 30; i++) {
        Task task = { .number = i };
        enqueue(task);
        printf("Produtor: adicionou tarefa %d\n", i);
        usleep(100000); // Pequena pausa entre produções
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_t prod_thread;

    // Criar threads consumidoras (thread pool)
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, worker, NULL);

    // Criar thread produtora
    pthread_create(&prod_thread, NULL, producer, NULL);

    // Espera o produtor terminar
    pthread_join(prod_thread, NULL);

    // Neste exemplo, as threads consumidoras não terminam
    // Em um sistema real, deveríamos sinalizar o encerramento

    // Para simplificação, dorme e depois encerra o programa
    sleep(5);
    printf("Encerrando programa.\n");
    return 0;
}
