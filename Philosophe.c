//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int n_of_philo;
int n_of_philoM;               // usefull if only eating alone

pthread_mutex_t *mutexTotal;
pthread_mutex_t *mutexBa;

void penser(int number){

}

/*
 * think then eat, Left handed (start by taking the left wand)
 */
void *gaucher(void *numbers){
    int itt=1;
    int number= (int) numbers;
    while(itt<=10000) {
        penser(number);
        pthread_mutex_lock(&mutexBa[number]);
        pthread_mutex_lock(&mutexBa[(number + 1) % n_of_philoM]);
        pthread_mutex_unlock(&mutexBa[number]);
        pthread_mutex_unlock(&mutexBa[(number + 1) % n_of_philoM]);
        itt++;
    }
}

/*
 * think then eat, Right handed (start by taking the right chopstick)
 */
void *droitier(void *numbers){
    int itt=1;
    int number= (int) numbers;
    while(itt<=10000) {
        penser(number);
        pthread_mutex_lock(&mutexBa[(number+1)%n_of_philoM]);
        pthread_mutex_lock(&mutexBa[number]);
        pthread_mutex_unlock(&mutexBa[(number+1)%n_of_philoM]);
        pthread_mutex_unlock(&mutexBa[number]);
        itt++;
    }

}



int main(int argc,char *argv[]){

    n_of_philo=atoi(argv[1]);
    n_of_philoM=n_of_philo;
    if(n_of_philo==1){n_of_philoM=2;}
    mutexBa= (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)*n_of_philoM);
    pthread_t threadsPhi[n_of_philo];

    for(int i=0;i<n_of_philoM;i++){
        pthread_mutex_init(mutexTotal,NULL);
        pthread_mutex_init(&mutexBa[i],NULL);
    }

    for(int i=0;i<n_of_philo;i++){
        if(i%2){
            pthread_create(&threadsPhi[i],NULL,gaucher,(void*) i);
        }
        else{
            pthread_create(&threadsPhi[i],NULL,droitier,(void*) i);
        }
    }
    for(int i=0;i<n_of_philo;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    free(mutexBa);
    return 0;
}


