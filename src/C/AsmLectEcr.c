#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "AsmMu.h"

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
        lock(ecriture);
        lock(mutLect);
        nLectActif++;
        if (nLectActif == 1) {
            lock(dbLock);
        }
        unlock(mutLect);
        unlock(ecriture);

        //lecture
        while (rand() > RAND_MAX / 10000) {}

        lock(mutLect);
        nLectActif--;
        if (nLectActif == 0) {
            unlock(dbLock);
        }
        //compteLectures++;
        unlock(mutLect);
    }
    //printf("lecteur terminé\n");
}

void *ecrivain(void *arg){
    for (int i = 0; i < 640; i++) {
        //printf("passage ecrivain nbr %i\n", i);
        lock(mutEcr);
        nEcrActif++;
        if (nEcrActif == 1) {
            lock(ecriture);
        }
        unlock(mutEcr);
        lock(dbLock);

        //ecriture
        while (rand() > RAND_MAX / 10000) {}


        unlock(dbLock);
        lock(mutEcr);
        nEcrActif--;
        if (nEcrActif == 0) {
            unlock(ecriture);
        }
        //compteEcritures++;
        unlock(mutEcr);
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
    create(mutLect);
    create(mutEcr);
    create(dbLock);
    create(ecriture);

    pthread_t ecrivains[(nEcr)];
    pthread_t lecteurs[(nLect)];

    for(int i = 0; i < nEcr; i++){
        err = pthread_create(&ecrivains[i],NULL,ecrivain,NULL);
        checkerr(err);}
    for(int i = 0; i < nLect; i++){
        err = pthread_create(&lecteurs[i],NULL,lecteur,NULL);
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
