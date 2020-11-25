//
//
//

int sem_create(int* sem, int start_val){
    int output;
    asm("movl %2, %%eax\n"
        "xchgl %%eax, (%1)\n"
        "movl %%eax, %0"
        : "=r" (output)
        : "r" (sem), "r"(start_val)
        : "%eax");
    return 0;
}

int sem_wait(int* sem){
    int output;
    asm("1:\n"
        "movl $0, %%eax\n"
        "xchgl %%eax, (%1)\n"
        "testl %%eax, %%eax\n"
        "jz 1b\n"
        "subl $1, %%eax\n"
        "movl %%eax, %0\n"
        "xchgl %%eax, (%1)\n"
        :"=r" (output)
        :"r" (sem)
        :"%eax");
    return output;
}

int sem_post(int *sem){
    int output;
    asm("movl $0, %%eax\n"
        "xchgl %%eax, (%1)\n"
        "addl $1, %%eax\n"
        "xchgl %%eax,(%1)\n"
        "addl $1, %%eax\n"
        "movl %%eax, %0\n"
        :"=r" (output) // no need of & because %eax it's already cloberred!
        :"r" (sem)
        :"%eax"
        );
    return output;
}