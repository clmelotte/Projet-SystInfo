//

#ifndef PROJET_SYSTINFO_ASMMUVT_H
#define PROJET_SYSTINFO_ASMMUVT_H

#include <stdlib.h>
#include <stdio.h>

int createVT(int* mutexAdress);

int lockVT(int* mutexAdress);

int lockcheckVT(int* mutexAdress);

int unlockVT(int* mutexAdress);
#endif //PROJET_SYSTINFO_ASMMUVT_H
