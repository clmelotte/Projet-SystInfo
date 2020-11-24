//
//
//

int main(int argc,char * argv[]){

}

int sem_create(int * sem, int size){
    int output;
    asm("movl %2, %%eax\n"
        "xchgl %%eax, (%1)\n"
        "movl %%eax, %0"
        : "=r" (output)
        : "r" (sem), "r"(size)
        : "%eax");
    return output != size;
}

int sem_wait(int * sem){
    int output;
    asm("\n"
        "\n"
        :"=r" (output)
        :"r" (sem)
        :"%eax");
}
