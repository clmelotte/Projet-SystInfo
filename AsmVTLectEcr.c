//
// Created by josep on 25/11/2020.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "AsmMuVT.h"

int nLectActif = 0;
int nEcrActif = 0;
int *mutLect;
int *mutEcr;
int *dbLock;
int *ecriture;

void checkerr(int err){
    if (err) {fprintf(stderr,"error err= %i \n", err); exit(-1); }}


void *lecteur(void *arg){

    for (int i = 0; i < 2560; i++) {
        //printf("passage lecteur nbr %i\n", i);
        lockVT(ecriture);
        lockVT(mutLect);
        nLectActif++;
        if (nLectActif == 1) {
            lockVT(dbLock);
        }
        unlockVT(mutLect);
        unlockVT(ecriture);

        //lecture
        while (rand() > RAND_MAX / 10000) {}

        lockVT(mutLect);
        nLectActif--;
        if (nLectActif == 0) {
            unlockVT(dbLock);
        }
        //compteLectures++;
        unlockVT(mutLect);
    }
    //printf("lecteur terminé\n");
}

void *ecrivain(void *arg){
    for (int i = 0; i < 640; i++) {
        //printf("passage ecrivain nbr %i\n", i);
        lockVT(mutEcr);
        nEcrActif++;
        if (nEcrActif == 1) {
            lockVT(ecriture);
        }
        unlockVT(mutEcr);
        lockVT(dbLock);

        //ecriture
        while (rand() > RAND_MAX / 10000) {}


        unlockVT(dbLock);
        lockVT(mutEcr);
        nEcrActif--;
        if (nEcrActif == 0) {
            unlockVT(ecriture);
        }
        //compteEcritures++;
        unlockVT(mutEcr);
    }
    //printf("ecrivain terminé\n");
}
/*
 * pre : nbr écrivains , nbr lecteurs
 */
int main(int argc, char *argv[]){
    int nEcr;
    int nLect;
    int err;

    if(argc != 3){
        printf("Error : Wrong number of arguments "
               "2 arguments are expected: nbr of writers, nbr of readers\n");
        exit(-1);
    }

    nEcr = atoi((char *)argv[1]);
    nLect = atoi((char *)argv[2]);

    /*
    if(nEcr ==0){
        printf("Warning: the input for the number of writers was either 0 or not a number \n");
    }
    if(nLect ==0){
        printf("Warning: the input for the number of readers was either 0 or not a number \n");
    }*/

    mutLect=(int *) malloc(sizeof(int));
    mutEcr=(int *) malloc(sizeof(int));
    dbLock=(int *) malloc(sizeof(int));
    ecriture=(int *) malloc(sizeof(int));
    createVT(mutLect);
    createVT(mutEcr);
    createVT(dbLock);
    createVT(ecriture);

    pthread_t ecrivains[(nEcr)];
    pthread_t lecteurs[(nLect)];
    void *emptyArgs;

    for(int i = 0; i < nEcr; i++){
        err = pthread_create(&ecrivains[i],NULL,ecrivain,emptyArgs);
        checkerr(err);}
    for(int i = 0; i < nLect; i++){
        err = pthread_create(&lecteurs[i],NULL,lecteur,emptyArgs);
        checkerr(err);}


    for(int i = 0; i < nEcr; i++){
        err = pthread_join(ecrivains[i],NULL);
        checkerr(err);}
    for(int i = 0; i < nLect; i++){
        err = pthread_join(lecteurs[i],NULL);
        checkerr(err);}

    free(mutLect);
    free(mutEcr);
    free(dbLock);
    free(ecriture);
    // printf("Travail terminé,\n passages Ecriture : %i\n passages Lecture : %i\n",compteEcritures,compteLectures);
}
