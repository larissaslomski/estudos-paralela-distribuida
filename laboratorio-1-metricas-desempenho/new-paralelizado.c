#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//#define IMPRIME

#define MAX_NUMBERS 500000000
//#define MAX_NUMBERS 10
#define MAX_VALUE 1000

float numbers[MAX_NUMBERS];

int init_numbers(){
  #pragma omp parallel
  {
    unsigned int seed = time(NULL) ^ omp_get_thread_num(); // semente única por thread
    #pragma omp for
    for (unsigned int i = 0; i < MAX_NUMBERS; i++) {
      numbers[i] = ((float)rand_r(&seed) / (float)RAND_MAX) * MAX_VALUE;
    }
  }
  return 0;
}

int show_numbers(){
  for (unsigned int i = 0; i < MAX_NUMBERS; i++)
    printf("number[%u] = %f\n", i, numbers[i]);
  return 0;
}

int main (int argc, char **argv){ 
  init_numbers();

  #ifdef IMPRIME
    show_numbers();
  #endif

  // Paraleliza também a operação matemática
  #pragma omp parallel for
  for (unsigned int i = 0; i < MAX_NUMBERS; i++){
    numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;    
  }  

  #ifdef IMPRIME
    printf("Apos a operacao matematica\n"); 
    show_numbers();
  #endif

  return 0;
}