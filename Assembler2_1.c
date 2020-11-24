//
// Created by joseph on 21/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int count;


int lock(int* mutexAdress){
    int output=1;


    asm ("movl %0, %%eax\n"
         "xchgl %%eax, %1\n"
         "movl %%eax, %0 "
         :"+m"(output)  // y is output operand
         :"m"(mutexAdress)   // x is input operand
         :"%eax"
         ); // %eax is clobbered register
         int b= *mutexAdress;
    printf("output After lock: %d, %d \n",output, b);

    return output;
}

int unlock(int* mutexAdress){
    int output=0;

    asm("movl %0 , %%eax\n"
        "xchgl %%eax, %1\n"
        "movl %%eax, %0"
        : "+m" ( output )
        : "m" (mutexAdress )
        : "%eax"
        );
    printf("after unlock :%d\n",output);

    return output;

}


void *SomTest(void* mut){
    for(int i =0; i<100;i++ ){
        while(lock((int*) mut)){}
        count++;
        unlock(mut);
    }
    return NULL;
}

int main(int argc,char *argv[]){
    printf("print number 1\n");
    int n_of_th = atoi(argv[1]);
    count=0;
    pthread_t threadsPhi[n_of_th];

    printf("print number 2\n");
    printf("print number of thread %d\n", n_of_th);

    int mut =0;

    for (int i=0; i<n_of_th; i++){
        pthread_create(&threadsPhi[i],NULL,SomTest,(void*) &mut);
    }
    printf("point de control 2\n");

    for(int i=0;i<n_of_th;i++) {
        pthread_join(threadsPhi[i], NULL);
    }
    printf("result \n");
    printf("result= %d", count);

    return 0;
}