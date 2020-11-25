#ifndef PROJET_SYSTINFO_ASMSEM_H
#define PROJET_SYSTINFO_ASMSEM_H

int sem_create(int* sem, int start_val);

int sem_wait(int* sem);

int sem_post(int *sem);

#endif //PROJET_SYSTINFO_ASMSEM_H
