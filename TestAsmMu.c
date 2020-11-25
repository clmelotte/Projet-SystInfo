//
// Created by josep on 25/11/2020.
//
#include "TestAsmMu.h"
#include "AsmMu.c"


int main(int argc,char *argv[]){
    if (argc != 2){printf("Error : Wrong number of arguments, "
                          "1 arguments is expected: nbr of philosophers\n");
        exit(-1);
    }


    int n_of_th = atoi(argv[1]);
    count=0;
    pthread_t threadsPhi[n_of_th];

    //printf("print number of thread %d\n", n_of_th);

    int mut =0;

    for (int i=0; i<n_of_th; i++){
        pthread_create(&threadsPhi[i],NULL,SomTest,(void*) &mut);
    }

    for(int i=0;i<n_of_th;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    printf("result= %d", count);
    return 0;
}


void *SomTest(void* mut){
    for(int i =0; i<6400;i++ ){
        lock((int*) mut);
        //while(rand() > RAND_MAX/10000){}
        count++;
        unlock((int*)mut);

    }
    return NULL;
}