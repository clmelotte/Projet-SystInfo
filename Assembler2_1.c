//
// Created by joseph on 21/11/2020.
//

#include <stdio.h>


int main(int argc,char* agrv[]){
    return 0;
}
int lock(void* mutexAdress){
    void *adress= mutexAdress;
    int output;

    asm ("movl $1, %0;xchgl %0, %1;"
    :"=r"(output)  /* y is output operand */
    :"r"(adress)   /* x is input operand */
    :); /* %eax is clobbered register */
    printf("adress= %s, output= %d", adress, output);
    return output;
}

int unlock(void* mutexAdress){

    void *adress= mutexAdress;
    int output;

    asm ("movl $0, %0;xchgl %0, %1;"
    :"=r"(output)  /* y is output operand */
    :"r"(adress)   /* x is input operand */
    :);

}

int lock2(){
    int output;
    return output;
}



int unlock2(){
    int output;
    return output;
}