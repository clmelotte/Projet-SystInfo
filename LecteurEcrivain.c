//
// Created by cloum on 18/11/2020.
//
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int nLectActif = 0;
int nEcrActif = 0;
int compteLectures = 0;
int compteEcritures = 0;
pthread_mutex_t mutLect;
pthread_mutex_t mutEcr;
pthread_mutex_t dbLock;
pthread_mutex_t ecriture;

void checkerr(int err){
    if (err) {fprintf(stderr,"error err= %i \n", err); exit(-1); }}


void *lecteur(void *arg){

    for (int i = 0; i < 2560; i++) {
        //printf("passage lecteur\n");
        pthread_mutex_lock(&ecriture);
        pthread_mutex_lock(&mutLect);
        nLectActif++;
        if (nLectActif == 1) {
            pthread_mutex_lock(&dbLock);
        }
        pthread_mutex_unlock(&mutLect);
        pthread_mutex_unlock(&ecriture);

        //lecture
        while (rand() > RAND_MAX / 10000) {}

        pthread_mutex_lock(&mutLect);
        nLectActif--;
        if (nLectActif == 0) {
            pthread_mutex_unlock(&dbLock);
        }
        compteLectures++;
        pthread_mutex_unlock(&mutLect);
    }
    //printf("lecteur terminé\n");
}

void *ecrivain(void *arg){
    for (int i = 0; i < 640; i++) {
        //printf("passage ecrivain\n");
        pthread_mutex_lock(&mutEcr);
        nEcrActif++;
        if (nEcrActif == 1) {
            pthread_mutex_lock(&ecriture);
        }
        pthread_mutex_unlock(&mutEcr);
        pthread_mutex_lock(&dbLock);

        //ecriture
        while (rand() > RAND_MAX / 10000) {}


        pthread_mutex_unlock(&dbLock);
        pthread_mutex_lock(&mutEcr);
        nEcrActif--;
        if (nEcrActif == 0) {
            pthread_mutex_unlock(&ecriture);
        }
        compteEcritures++;
        pthread_mutex_unlock(&mutEcr);
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
               "2 arguments are expected: nbr of writers, nbr of readers");
        exit(-1);
    }

    nEcr = atoi((char *)argv[1]);
    nLect = atoi((char *)argv[2]);

    if(nEcr ==0){
        printf("Warning: the input for the number of writers was either 0 or not a number \n");
    }
    if(nLect ==0){
        printf("Warning: the input for the number of readers was either 0 or not a number \n");
    }

    err=pthread_mutex_init(&mutEcr,NULL);
    checkerr(err);
    err=pthread_mutex_init(&mutLect,NULL);
    checkerr(err);
    err=pthread_mutex_init(&ecriture,NULL);
    checkerr(err);
    err=pthread_mutex_init(&dbLock,NULL);
    checkerr(err);

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

    printf("Travail terminé,\n passages Ecriture : %i\n passages Lecture : %i\n",compteEcritures,compteLectures);
}