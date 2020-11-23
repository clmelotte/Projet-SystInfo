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
    printf("entre Lock\n");
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
    printf("entre SomTest\n")
    for(int i =0; i<100;i++ ){
        while(lock(mut)==1){}
        *count++;
        unlock(mut);
    }
    return NULL;
}

int main(int argc,char *argv[]){
    printf("print number 1\n");
    int n_of_th = atoi(argv[1]);
    pthread_t threadsPhi[n_of_th];
    printf("print number 2\n");
    printf("print number of thread %d", n_of_th);
    omega = 1;
    int *mut= &omega;

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