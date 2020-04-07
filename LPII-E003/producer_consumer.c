#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

#define NUM_THREADS 3


sem_t semph;
sem_t sleeping;
pthread_mutex_t mutex;
char buffer;
int g_id = 0;

void Produce(char message);
char Consume();
void * Producer(void * id);
void * Consumer(void * id);


int main(){
	pthread_t th_producer, th_consumer;

    pthread_mutex_init(&mutex, NULL);
	sem_init(&semph, 0, 1);
	sem_init(&sleeping, 0 , 0);
	
    pthread_create(&th_producer, NULL, Producer, (void *)0);
    pthread_create(&th_consumer, NULL, Consumer, (void *)1);
	
    pthread_join(th_producer, NULL);
    pthread_join(th_consumer, NULL);

    pthread_mutex_destroy(&mutex);
	sem_destroy(&semph);
    sem_destroy(&sleeping);

	return 0;
}

void Produce(char message){
    buffer = message;
    printf("Produtor: Envia %c para o buffer\t", message);
}

char Consume(){
    char message;

    message = buffer;
    printf("Consumidor: Recebe %c do buffer\n", message);
    
    return message;
}

void * Producer(void * id){
	int t_id = (int) id;
	char * msg = "ABRACADABRA SIMSALABIM";

    int i = 0;
    while( i <= 23){
        sem_wait(&semph);

        pthread_mutex_lock(&mutex);
        
        if(g_id == t_id){
            Produce(msg[i]);        //Sessão Crítica
            i++;
            g_id = 1;
        }

        pthread_mutex_unlock(&mutex);

        sem_post(&semph);
        sleep(1);

    }

    pthread_exit(NULL);

}

void * Consumer(void * id){
    int t_id = (int) id;
	char message[25];
    char aux;

    int i = 0;
    while(i <= 23){
        sem_wait(&semph);

        pthread_mutex_lock(&mutex);
        
        if(g_id == t_id){
            aux = Consume();        //Sessão Crítica
            message[i] = aux;
            i++;
            g_id = 0;
        }
        pthread_mutex_unlock(&mutex);

        sem_post(&semph);
        sleep(1);

    }
    
    message[25] = '\n';
    printf("Mensagem recebida: Tamanho[%ld]; Conteudo[%s]\n",strlen(message), message);
    pthread_exit(NULL);

}