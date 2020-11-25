//
// Created by josep on 25/11/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "AsmMu.h"

int* mut;

void *SomTest(void* mutx){
    for(int i =0; i<6400;i++ ){
        lock((int*) mutx);
        while(rand() > RAND_MAX/10000){}
        unlock((int*) mutx);

    }
    return NULL;
}

int main(int argc,char *argv[]){
    if (argc != 2){printf("Error : Wrong number of arguments, "
                          "1 arguments is expected: nbr of philosophers\n");
        exit(-1);
    }


    int n_of_th = atoi(argv[1]);
    pthread_t threadsPhi[n_of_th];


    mut =(int*) malloc(sizeof(int));
    create(mut);

    for (int i=0; i<n_of_th; i++){
        pthread_create(&threadsPhi[i],NULL,SomTest,(void*) mut);
    }

    for(int i=0;i<n_of_th;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    return 0;
}


