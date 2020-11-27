//
// Created by josep on 27/11/2020.
//

#ifndef PROJET_SYSTINFO_ASMMUBOFF_H
#define PROJET_SYSTINFO_ASMMUBOFF_H


typedef struct mutexBOff{
    int * mutexAdress;
    int denIni;
    int denFinal;
}mutexBOff_t;


int createBOff(mutexBOff_t mutBOff,int* mutexAdress, int denIni, int denFin);

int lockBOff(mutexBOff_t mutBOff);

int lockcheckBOff(mutexBOff_t mutBOff);

int unlockBOff(mutexBOff_t mutBOff);
#endif //PROJET_SYSTINFO_ASMMUBOFF_H
