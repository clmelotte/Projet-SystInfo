#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <semaphore.h>
#include "AsmMu.h"

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
sem_t full;
sem_t empty;

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
        lock(in);
        //printf("lock done\n");
        //probably harms efficiency a bit, but assure no deadlock will occur
        if(inLeft<1){
            unlock(in);
            break;}
        inLeft--;
        unlock(in);



        //producing a random number ans simulating computing:
        int nbr = rand();
        while (rand() > RAND_MAX / 10000) {}

        sem_wait(&empty);
        lock(buffer);
        put(nbr);
        unlock(buffer);
        sem_post(&full);

        //printf("producing done, nbr given: %i\n", nbr);
    }
}

void *consommateur(void *args){
    while (outDone<1024) {
        int nbr;
        //printf("consuming started, done: %i\n", outDone);
        lock(out);
        //printf("lock done\n");
        //probably harms efficiency a bit, but assures no deadlock will occur
        if(outDone>1023){
            unlock(out);
            break;}
        outDone++;
        unlock(out);

        sem_wait(&full);
        lock(buffer);
        nbr = get();
        unlock(buffer);
        sem_post(&empty);

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

    /*
    int inValue=0;
    int outValue=0;
    int bufferValue=0;  
    in=&inValue;
    out=&outValue;
    buffer=&bufferValue;
     */

    in = (int*) malloc(sizeof(int));
    out = (int*) malloc(sizeof(int));
    buffer = (int*) malloc(sizeof(int));
    create(in);
    create(out);
    create(buffer);

    err=sem_init(&full,1,0);
    checkerr(err);
    err=sem_init(&empty,1,8);
    checkerr(err);

    pthread_t producteurs[(nProd)];
    pthread_t consommateurs[(nCons)];
    void *emptyArgs;

    for(int i = 0; i < nProd; i++){
        err=pthread_create(&producteurs[i],NULL,producteur,emptyArgs);
        checkerr(err);}
    for(int i = 0; i < nCons; i++){
        err=pthread_create(&consommateurs[i],NULL,consommateur,emptyArgs);
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
    //printf("Travail terminé,\n productions restantes : %i\n consommations faites : %i\n",inLeft,outDone);
}
