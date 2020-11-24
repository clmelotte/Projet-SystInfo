//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int n_of_philo;
int n_of_philoM;

pthread_mutex_t mutexBa[32];

void penser(int number){

}

/*
 * think then eat, Left handed (start by taking the left wand)
 */
void *gaucher(void *numbers){
    int itt=1;
    int number= *((int*) numbers);
    while(itt<=100000) {
        penser(number);
        pthread_mutex_lock(&mutexBa[number]);
        pthread_mutex_lock(&mutexBa[(number + 1) % n_of_philoM]);
        pthread_mutex_unlock(&mutexBa[number]);
        pthread_mutex_unlock(&mutexBa[(number + 1) % n_of_philoM]);
        itt++;
    }
    printf("fini %d\n",number);
    return NULL;
}

/*
 * think then eat, Right handed (start by taking the right chopstick)
 */
void *droitier(void *numbers){
    int itt=1;
    int number= *((int*) numbers);
    while(itt<=100000) {
        penser(number);
        pthread_mutex_lock(&mutexBa[(number+1)%n_of_philoM]);
        pthread_mutex_lock(&mutexBa[number]);
        pthread_mutex_unlock(&mutexBa[(number+1)%n_of_philoM]);
        pthread_mutex_unlock(&mutexBa[number]);
        itt++;
    }
    printf("fini %d\n",number);
    return NULL;
}



int main(int argc,char *argv[]){
    printf("entre\n");
    n_of_philo=atoi(argv[1]);
    n_of_philoM=n_of_philo;
    if(n_of_philo==1){n_of_philoM=2;}
    pthread_t threadsPhi[n_of_philo];

    for(int i=0;i<n_of_philoM;i++){
        pthread_mutex_init(&mutexBa[i],NULL);
    }

    for(int i=0;i<n_of_philo;i++){
        printf("i= %d\n", i);
        if(i==0){
            pthread_create(&threadsPhi[i],NULL,gaucher,(void*) &i);
        }
        else{
            pthread_create(&threadsPhi[i],NULL,droitier,(void*) &i);
        }
    }
    for(int i=0;i<n_of_philo;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    printf("réussiiiiiiii ?!");
    return 0;
}
