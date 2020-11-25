//
// Created by josep on 25/11/2020.
//
#include <stdlib.h>
#include <stdio.h>
#ifndef PROJET_SYSTINFO_ASMMUVT_H
#define PROJET_SYSTINFO_ASMMUVT_H
int createVT(int* mutexAdress);

int lockVT(int* mutexAdress);

int lockcheckVT(int* mutexAdress);

int unlockVT(int* mutexAdress);
#endif //PROJET_SYSTINFO_ASMMUVT_H
