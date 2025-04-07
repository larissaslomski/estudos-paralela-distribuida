#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define IMPRIME

#define MAX_NUMBERS 500000000
//#define MAX_NUMBERS 10
#define MAX_VALUE 1000;

float numbers[MAX_NUMBERS];
unsigned int i;

/* Esta versao tera problemas de desempenho ao paralelizar com threads
POSIX.1c requires that there is mutual exclusion for the `rand' and
`srand' functions to prevent concurrent calls from modifying common
data.
Isso sugere que a funcao rand() utiliza um mutex internamente, prejudicando o desempenho 
ao paralelizar a rotina a seguir
Uma alternativa seria utilizar a funcao rand_r(), que utiliza uma variavel local para armazenar 
o estado para geracao de numeros pseudo-aleatorios.
*/
int init_numbers(){
  for(i = 0; i < MAX_NUMBERS; i++)
    numbers[i] = ((float)rand()/(float)RAND_MAX) * MAX_VALUE;
  return 0;
}

int show_numbers(){
  for (i = 0; i < MAX_NUMBERS; i++)
    printf("number[%u] = %f\n",i,numbers[i]);
  return 0;
}

int main (int argc, char **argv){
  srand(time(NULL));
 
  init_numbers();

  #ifdef IMPRIME
    show_numbers();
  #endif
 
  for (i = 0; i < MAX_NUMBERS; i++){
    numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;    
  }  

  #ifdef IMPRIME
    printf("Apos a operacao matematica\n"); 
    show_numbers();
  #endif

  return 0;
}