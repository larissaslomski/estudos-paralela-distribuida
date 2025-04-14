//pthread_create(onde criar, null, funcao que thread executa, argumentos dessa funcao)



int ha_comida_no_quintal = 0;


int comeu_comida = 0;
quintal_vazio;
pthread_mutex_t mutex;

//bob
void *colocar_comida(void *arg){
  if lata levantada:
    printf("Bob entrou no quintal\n");
    printf("Bob colocou comida\n");
    derrubar_lata();
}


//alice
void *soltar_cachorros(void *arg){
  if lata_caida:
    printf("Cachorro entrou no quintal\n");
    printf("Cachorros comendo\n");
  if comida_terminou:
    levantar_lata();
}


int main (int argc, char **argv){



 

  sem_init(&cliente, 0, 0);
  sem_init(&barbeiro, 0, 0);
  sem_init(&cliente_pronto, 0, 0);
  sem_init(&barbeiro_pronto, 0, 0);

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&threads[i],NULL,thread_barbeiro,NULL);  

  for(i = 1; i < n_threads; i++){
    ids[i] = i-1;
    pthread_create(&threads[i],NULL,thread_cliente,&ids[i]);
  }

  for(i = 1; i < n_threads; i++){
    pthread_join(threads[i],NULL);
  }

  printf("Nao ha mais clientes\n");
  pthread_cancel(threads[0]); // o barbeiro

  sem_destroy(&cliente);
  sem_destroy(&barbeiro);
  sem_destroy(&cliente_pronto);
  sem_destroy(&barbeiro_pronto);
  pthread_mutex_destroy(&mutex);

  return 0;
}
