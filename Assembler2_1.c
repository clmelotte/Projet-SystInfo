//
// Created by joseph on 21/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int count;


int lock(int* mutexAdress){
    int output;
    printf("Mutex adress dans lock: %p avec %d\n", mutexAdress, *mutexAdress );

    asm ("movl $1, %%eax\n"
         "xchgl %%eax, (%1)\n"
         "movl %%eax, %0 "
         :"=r"(output)  // y is output operand
         :"r"(mutexAdress)   // x is input operand
         :"%eax"
         ); // %eax is clobbered register
         printf("output : %d \n",output);
    printf("count %d \n",count);




    return output;
}

int unlock(int* mutexAdress){
    int output;
    printf("Mutex adress dans unlock: %p avec valeur %d\n", mutexAdress, *mutexAdress );

    asm("movl $0 , %%eax\n"
        "xchgl %%eax, (%1)\n"
        "movl %%eax, %0"
        : "=r" ( output )
        : "r" (mutexAdress )
        : "%eax"
        );
    printf("after unlock :%d\n",output);


    return output;

}


void *SomTest(void* mut){
    for(int i =0; i<100;i++ ){
        while(lock((int*) mut)){}
        count++;
        unlock((int*)mut);
    }
    return NULL;
}

int main(int argc,char *argv[]){


    int n_of_th = atoi(argv[1]);
    count=0;
    pthread_t threadsPhi[n_of_th];

    printf("print number of thread %d\n", n_of_th);

    int mut =0;
    printf("adress sous format int : %d\n", ((int) &mut));

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