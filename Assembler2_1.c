//
// Created by joseph on 21/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int omega;
int *mut;
int *count;


long lock(int* mutexAdress){
    int *adress= mutexAdress;
    int output=0;
    printf("non");
/*
    asm ("movl %0 , %%eax\n"
         "xchgl %%eax, %1\n"
         "movl %%eax, %0 "
         :"=m"(output)  // y is output operand
         :"m"(adress)   // x is input operand
         :"eax"
         ); // %eax is clobbered register
         */
    return output;
}

long unlock(int* mutexAdress){
    int *adress= mutexAdress;
    int output=0;
    printf("oui");
/*
    asm("movl %0 , %%eax\n"
        "xchgl %%eax, %1\n"
        "movl %%eax, %0 "
        :"=m"(output)
        :"m"(adress)
        :"eax"
        );
        */
    return output;

}


void *SomTest(){
    for(int i =0; i<1000;i++ ){
        while(lock(mut)==1){}
        *count++;
        unlock(mut);
    }
    return NULL;
}

int main(int argc,char *argv[]){
    printf("mais print! putain!\n");

    omega = 1;
    int n_of_th = atoi(argv[1]);
    pthread_t threadsPhi[n_of_th];
    printf("1\n");
    printf("%d", n_of_th);

    for (int i=0; i<n_of_th; i++){
        pthread_create(&threadsPhi[i],NULL,SomTest,NULL);
    }
    printf("2");

    for(int i=0;i<n_of_th;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    printf("result= %d", *count);

    return 0;
}