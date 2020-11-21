//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



int n_of_philo;
int totalEat;                  //Total of finished Threads

pthread_mutex_t *mutexTotal;
pthread_mutex_t *mutexBa;

void penser(int number){
    printf("Philosophe %d pense \n", number+1);
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
        pthread_mutex_lock(&mutexBa[(number + 1) % n_of_philo]);
        printf("philosophe gaucher %d mange %d \n", number+1, itt);
        pthread_mutex_unlock(&mutexBa[number]);
        pthread_mutex_unlock(&mutexBa[(number + 1) % n_of_philo]);
        itt++;
    }
    pthread_mutex_lock(&mutexTotal);
    totalEat++;
    pthread_mutex_unlock(&mutexTotal);
    printf("philosophe %d a fini !\n",number+1);
}

/*
 * think then eat, Right handed (start by taking the right wand)
 */
void *droitier(void *numbers){
    int itt=1;
    int number= (int) numbers;
    while(itt<=10000) {
        penser(number);
        pthread_mutex_lock(&mutexBa[(number+1)%n_of_philo]);
        pthread_mutex_lock(&mutexBa[number]);
        printf("philosophe droitier %d mange %d \n", number+1, itt);
        pthread_mutex_unlock(&mutexBa[(number+1)%n_of_philo]);
        pthread_mutex_unlock(&mutexBa[number]);
        itt++;
    }
    pthread_mutex_lock(&mutexTotal);
    totalEat++;
    pthread_mutex_unlock(&mutexTotal);
    printf("philosophe %d a fini !\n",number+1);

}



void main(int argc,char *argv[]){

    time_t timed = time(NULL);

    n_of_philo=atoi(argv[1]);
    mutexBa= (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)*n_of_philo);
    pthread_t threadsPhi[n_of_philo];
    printf("number of philos: %d \n",n_of_philo);

    for(int i=0;i<n_of_philo;i++){
        pthread_mutex_init(mutexTotal,NULL);
        pthread_mutex_init(&mutexBa[i],NULL);
        if(i%2){
            pthread_create(&threadsPhi[i],NULL,gaucher,(void*) i);
            printf("philo %d crée gaucher \n", i);
        }
        else{
            pthread_create(&threadsPhi[i],NULL,droitier,(void*) i);
            printf("philo %d crée droitier \n", i);
        }
    }
    for(int i=0;i<n_of_philo;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    free(mutexBa);
    printf("total est égal %d\n",totalEat);
    printf("temps = %ld",(time(NULL)-timed) );
}


