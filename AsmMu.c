#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "AsmMu.h"

//int count;

int create(int* mutexAdress){
    int output;
    printf("entrer %d",*mutexAdress);
    asm ("movl $0, %%eax\n"
         "xchgl %%eax, (%1)\n"
         "movl %%eax, %0"
    :"=r" (output)
    :"r" (mutexAdress)
    :"%eax"
    );
    return 0;
}

int lock(int* mutexAdress){
    int output;
    //printf("Mutex adress dans lock: %p avec %d\n", mutexAdress, *mutexAdress );

    asm ("1:\n"
         "movl $1, %%eax\n"
         "xchgl %%eax, (%1)\n"
         "testl %%eax,%%eax\n"
         "jnz 1b\n"
         "movl %%eax, %0\n" //usefull in cas of problem
         :"=r"(output)  // y is output operand
         :"r"(mutexAdress)   // x is input operand
         :"%eax"
         ); // %eax is clobbered register
         // printf("output : %d \n",output);
    //printf("count %d \n",count);

    return output;
}

int unlock(int* mutexAdress){
    int output;
    //printf("Mutex adress dans unlock: %p avec valeur %d\n", mutexAdress, *mutexAdress );

    asm("movl $0 , %%eax\n"
        "xchgl %%eax, (%1)\n"
        "movl %%eax, %0\n"
        : "=r" ( output )
        : "r" (mutexAdress )
        : "%eax"
        );
    //printf("after unlock :%d\n",output);

    return output;

}


void *SomTest(void* mut){
    for(int i =0; i<6400;i++ ){
        lock((int*) mut);
        while(rand() > RAND_MAX/10000){}
        //count++;
        unlock((int*)mut);

    }
    return NULL;
}
/*
int main(int argc,char *argv[]){


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
    //printf("result= %d", count);
    return 0;
}*/
