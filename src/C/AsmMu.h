#include <stdlib.h>
#include <stdio.h>
#ifndef PROJET_SYSTINFO_ASMMU_H
#define PROJET_SYSTINFO_ASMMU_H

//int count;

int create(int* mutexAdress);

int lock(int* mutexAdress);

int unlock(int* mutexAdress);

#endif //PROJET_SYSTINFO_ASMMU_H
