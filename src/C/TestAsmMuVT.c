//
// Created by josep on 25/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "AsmMuVT.h"


int* mut;

void *SomTestVT(void* mutx){
    for(int i =0; i<6400;i++ ){
        lockVT((int*) mutx);
        while(rand() > RAND_MAX/10000){}
        unlockVT((int*) mutx);

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
    createVT(mut);

    for (int i=0; i<n_of_th; i++){
        pthread_create(&threadsPhi[i],NULL,SomTestVT,(void*) mut);
    }

    for(int i=0;i<n_of_th;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    free(mut);
    return 0;
}


