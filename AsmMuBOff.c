//
// Created by josep on 27/11/2020.
//
#include <stdlib.h>
#include "AsmMuBOff.h"


/*
 * input: int* that's already malloc!
 */



int createBOff(mutexBOff_t mutBOff,int* mutexAdress, int denIni, int denFin){
    int output;
    if(mutexAdress==NULL || denIni<=0 || denFin < denIni){return 1;}
    mutBOff.mutexAdress=mutexAdress;
    mutBOff.denIni=denIni;
    mutBOff.denFinal=denFin;
    asm ("movl $0, %%eax\n"
         "xchgl %%eax, (%1)\n"
         "movl %%eax, %0"
    :"=r" (output)
    :"r" (mutexAdress)
    :"%eax"
    );
    return 0;
}



int lockBOff(mutexBOff_t mutBOff){
    int output=0;
    int denIni = mutBOff.denIni;
    int denFin = mutBOff.denFinal;
    while(lockcheckBOff(mutBOff)){
        while(rand() > RAND_MAX/denIni){}
        denIni=denIni*2;
        if(denIni>denFin){denIni=denFin;}
    }
    return output;
}

/*
 * Output: 0 if can continue or 1 if it can't.
 */
int lockcheckBOff(mutexBOff_t mutBOff){
    int output;
    int* mutexAdress = mutBOff.mutexAdress;
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

int unlockBOff(mutexBOff_t mutBOff){
    int output;
    int* mutexAdress = mutBOff.mutexAdress;

    asm("movl $0 , %%eax\n"
        "xchgl %%eax, (%1)\n"
        "movl %%eax, %0\n"
    : "=r" ( output )
    : "r" (mutexAdress )
    : "%eax"
    );

    return output;

}




