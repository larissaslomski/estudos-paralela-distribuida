#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>


sem_t lata_em_pe;   // Permite Bob colocar comida (produtor)
sem_t lata_caida;   // Permite Alice soltar os bichos (consumidor)

int comida_no_quintal = 0;

void* bob(void* arg) {
    while (1) {
        sem_wait(&lata_em_pe);  
        printf("Bob: Coloca comida no quintal.\n");
        comida_no_quintal = 1;

        printf("Bob: Derruba a lata.\n");
        sem_post(&lata_caida);  

        sleep(rand() % 6); 
    }
    return NULL;
}

void* alice(void* arg) {
    while (1) {
        sem_wait(&lata_caida); 

        printf("Alice: Solta os cachorros para comer.\n");
        sleep(rand() % 6);; 

        printf("Alice: Cachorros param de comer.\n");
        comida_no_quintal = 0;

        printf("Alice: Levanta a lata.\n");
        sem_post(&lata_em_pe);  
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t thread_bob, thread_alice;

    sem_init(&lata_em_pe, 0, 1);   // Começa com lata em pé
    sem_init(&lata_caida, 0, 0);   // Começa com lata caída 

    pthread_create(&thread_bob, NULL, bob, NULL);
    pthread_create(&thread_alice, NULL, alice, NULL);

    pthread_join(thread_bob, NULL);
    pthread_join(thread_alice, NULL);

    sem_destroy(&lata_em_pe);
    sem_destroy(&lata_caida);

    return 0;
}
