#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "AsmMuVT.h"
#include "AsmSem.h"

int inLeft;
int outDone;

int *buff;
int buffIn;
int buffLen;
int buffFirstFree;
int buffFirstFull;

int *in;
int *out;
int *buffer;
int *full;
int *empty;

void checkerr(int err){
    if (err) {fprintf(stderr,"error err= %i \n", err); exit(-1); }}
void checkalloc(int condition){
    if (condition){fprintf(stderr,"calloc/malloc fail\n");exit(-1);}
}


int put(int n){
    if(buffIn==buffLen){return -1;}
    buff[buffFirstFree]=n;
    buffFirstFree=(buffFirstFree+1)%buffLen;
    buffIn++;
    return 0;
}

int get(){
    if(!buffIn){return -1;}
    int value=buff[buffFirstFull];
    buffFirstFull=(buffFirstFull+1)%buffLen;
    buffIn--;
    return value;
}

void *producteur(void *args){
    while (inLeft>0) {
        //printf("producing started, left: %i\n", inLeft);
        lockVT(in);
        //printf("lock done\n");
        //probably harms efficiency a bit, but assures no deadlock will occur
        if(inLeft<1){
            unlockVT(in);
            break;}
        inLeft--;
        unlockVT(in);

        //producing a random number ans simulating computing:
        int nbr = rand();
        while (rand() > RAND_MAX / 10000) {}

        sem_wait(empty);
        lockVT(buffer);
        put(nbr);
        unlockVT(buffer);
        sem_post(full);

        //printf("producing done, nbr given: %i\n", nbr);
    }
}

void *consommateur(void *args){
    while (outDone<1024) {
        int nbr;
        //printf("consuming started, done: %i\n", outDone);
        lockVT(out);
        //printf("lock done\n");
        //probably harms efficiency a bit, but assures no deadlock will occur
        if(outDone>1023){
            unlockVT(out);
            break;}
        outDone++;
        unlockVT(out);
        sem_wait(full);
        lockVT(buffer);
        nbr = get();
        unlockVT(buffer);
        sem_post(empty);

        //simulating computing;
        while (rand() > RAND_MAX / 10000) {}
        //printf("consuming done, outDone: %i\n", outDone);
    }

}

int main(int argc, char *argv[]){
    int nProd;
    int nCons;
    int err;

    if(argc != 3){
        printf("Error : Wrong number of arguments "
               "2 arguments are expected: nbr of producers, nbr of consumers\n");
        exit(-1);
    }

    nProd=atoi((char *)argv[1]);
    nCons=atoi((char *)argv[2]);

    inLeft=1024;
    outDone=0;
    buff=(int *) calloc(8,sizeof(int));
    checkalloc(buff==NULL);
    buffIn=0;
    buffLen=8;
    buffFirstFree=0;
    buffFirstFull=0;

    in = (int*) malloc(sizeof(int));
    out = (int*) malloc(sizeof(int));
    buffer = (int*) malloc(sizeof(int));
    createVT(in);
    createVT(out);
    createVT(buffer);

    full = (int *) malloc(sizeof(int));
    empty = (int *) malloc(sizeof(int));
    sem_create(full,0);
    sem_create(empty,8);

    pthread_t producteurs[(nProd)];
    pthread_t consommateurs[(nCons)];

    for(int i = 0; i < nProd; i++){
        err=pthread_create(&producteurs[i],NULL,producteur,NULL);
        checkerr(err);}
    for(int i = 0; i < nCons; i++){
        err=pthread_create(&consommateurs[i],NULL,consommateur,NULL);
        checkerr(err);}


    for(int i = 0; i < nProd; i++){
        err=pthread_join(producteurs[i],NULL);
        checkerr(err);}
    //printf("producer nbr %i closed\n",i+1);}

    for(int i = 0; i < nCons; i++){
        err=pthread_join(consommateurs[i],NULL);
        checkerr(err);}
    //printf("consumer nbr %i closed\n",i+1);}

    free(buff);
    free(in);
    free(out);
    free(buffer);
    free(full);
    free(empty);
    //printf("Travail terminé,\n productions restantes : %i\n consommations faites : %i\n",inLeft,outDone);
}
