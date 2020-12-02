

//
// Created by josep on 02/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "AsmMuBOff.h"

int count ;

void *SomTest(void* mutx){

    mutexBOff_t *mut = (mutexBOff_t *) mutx;
    for(int i =0; i<6400;i++ ){
        lockBOff(mut);
        while(rand() > RAND_MAX/10000){}
        unlockBOff(mut);
    }
    return NULL;
}

int main(int argc,char *argv[]){
    if (argc != 4){printf("Error : Wrong number of arguments, "
                          "3 arguments is expected: nbr of threads, den ini, den max\n");
        exit(-1);
    }

    count =0;


    int n_of_th = atoi(argv[1]);
    int denIni = atoi(argv[2]);
    int denMax = atoi(argv[3]);
    pthread_t threadsPhi[n_of_th];


    mutexBOff_t* mut =(mutexBOff_t *) malloc(sizeof(mutexBOff_t));
    mut->mutexAdress = (int*) malloc(sizeof(int));

    createBOff(mut, mut->mutexAdress, denIni, denMax);

    for (int i=0; i<n_of_th; i++){
        pthread_create(&threadsPhi[i],NULL,SomTest,(void*) mut);
    }

    for(int i=0;i<n_of_th;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    free(mut->mutexAdress);
    free(mut);
    if(count == 6400*n_of_th){return 0;}
    else {return -1;}

}

