//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "AsmMu.h"


int n_of_philo;
int n_of_philoM;

int *mutexBa[16];


/* pré: receive the int err (the return form the tested function)
 * post: ---
 * it's stop the programme and print a error if err=-1 */
void checkerr(int err){
    if (err) {fprintf(stderr,"error err= %i \n", err); exit(-1); }}

/*
 * Think...
 */
void penser(int number){

}

/*
 * think then eat, Left handed (start by taking the left wand)
 */
void *gaucher(void *numbers){
    int itt=1;
    int number= *((int*) numbers);
    while(itt<=1000000) {
        penser(number);
        lock(mutexBa[number]);
        lock(mutexBa[(number + 1) % n_of_philoM]);
        unlock(mutexBa[number]);
        unlock(mutexBa[(number + 1) % n_of_philoM]);
        itt++;
    }
    //printf("fini %d\n",number);
    return NULL;
}

/*
 * think then eat, Right handed (start by taking the right chopstick)
 */
void *droitier(void *numbers){
    int itt=1;
    int number= *((int*) numbers);
    while(itt<=1000000) {
        penser(number);
        lock(mutexBa[(number+1)%n_of_philoM]);
        lock(mutexBa[number]);
        unlock(mutexBa[(number+1)%n_of_philoM]);
        unlock(mutexBa[number]);
        itt++;
    }
    //printf("fini %d\n",number);
    return NULL;
}



int main(int argc,char *argv[]){

    int err;
    //printf("entre\n");
    n_of_philo=atoi(argv[1]);
    n_of_philoM=n_of_philo;
    if(n_of_philo==1){n_of_philoM=2;}
    pthread_t threadsPhi[n_of_philo];
    int tabI[n_of_philo];
    int values[16];

    for(int i=0;i<n_of_philoM;i++){
        mutexBa[i]=(int *) malloc(sizeof(int));
        create(mutexBa[i]);
    }

    for(int i=0;i<n_of_philo;i++){
        //printf("i= %d\n", i);
        tabI[i]=i;
        if(i==0){
            err=pthread_create(&threadsPhi[i],NULL,gaucher,(void*) &(tabI[i]));
            checkerr(err);

        }
        else{
            err=pthread_create(&threadsPhi[i],NULL,droitier,(void*) &(tabI[i]));
            checkerr(err);
        }
    }
    for(int i=0;i<n_of_philo;i++) {
        err=pthread_join(threadsPhi[i], NULL);
        checkerr(err);
    }

    for(int i=0;i<n_of_philoM;i++){
        free(mutexBa[i]);
    }

    return 0;
}
