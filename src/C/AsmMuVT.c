//
//
//
#import "AsmMuVT.h"


/*
 * input: int* that's already malloc!
 */
int createVT(int* mutexAdress){
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



int lockVT(int* mutexAdress){
    int output=0;
    while(lockcheckVT(mutexAdress)){
        while(*mutexAdress==1){}
    }
    return output;
}

/*
 * Output: 0 if can continue or 1 if it can't.
 */
int lockcheckVT(int* mutexAdress){
    int output;
    asm ("1:\n"
         "movl $1, %%eax\n"
         "xchgl %%eax, (%1)\n"
         "movl %%eax, %0\n"  // return 0 if can continue or 1 else
    :"=r"(output)  // output operand
    :"r"(mutexAdress)   //  input operand
    :"%eax"
    ); // %eax is clobbered register
    return output;
}

int unlockVT(int* mutexAdress){
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

