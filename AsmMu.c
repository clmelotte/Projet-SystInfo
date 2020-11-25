
#include "AsmMu.h"


/*
 * input: int* that's already malloc!
 */
int create(int* mutexAdress){
    int output;
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


    return output;
}

int unlock(int* mutexAdress){
    int output;

    asm("movl $0 , %%eax\n"
        "xchgl %%eax, (%1)\n"
        "movl %%eax, %0\n"
        : "=r" ( output )
        : "r" (mutexAdress )
        : "%eax"
        );

    return output;

}

