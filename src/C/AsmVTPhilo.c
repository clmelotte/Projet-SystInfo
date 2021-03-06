//
// Created by josep on 25/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "AsmMuVT.h"

int n_of_philo;
int n_of_philoM;

int *mutexBa[32];


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
        lockVT(mutexBa[number]);
        lockVT(mutexBa[(number + 1) % n_of_philoM]);
        unlockVT(mutexBa[number]);
        unlockVT(mutexBa[(number + 1) % n_of_philoM]);
        itt++;
    }
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
        lockVT(mutexBa[(number+1)%n_of_philoM]);
        lockVT(mutexBa[number]);
        unlockVT(mutexBa[(number+1)%n_of_philoM]);
        unlockVT(mutexBa[number]);
        itt++;
    }
    return NULL;
}



int main(int argc,char *argv[]){

    int err;
    n_of_philo=atoi(argv[1]);
    n_of_philoM=n_of_philo;
    if(n_of_philo==1){n_of_philoM=2;}
    pthread_t threadsPhi[n_of_philo];
    int tabI[n_of_philo];

    for(int i=0;i<n_of_philoM;i++){
        mutexBa[i]=(int *) malloc(sizeof(int));
        createVT(mutexBa[i]);
    }

    for(int i=0;i<n_of_philo;i++){
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
