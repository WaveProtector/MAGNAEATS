#include "synchronization.h"
#include "fcntl.h"

sem_t * semaphore_create(char* name, int value) {
    return sem_open(name, O_CREAT, 0xFFFFFFFF, value);
}

void semaphore_destroy(char* name, sem_t* semaphore) {
    sem_close(semaphore);
    sem_unlink(name);
}

void produce_begin(struct prodcons* pc) {
    sem_wait(pc->empty);
    sem_wait(pc->mutex);
}

void produce_end(struct prodcons* pc) {
    sem_post(pc->mutex);
    sem_post(pc->full);
}

void consume_begin(struct prodcons* pc) {
    sem_wait(pc->full);
    sem_wait(pc->mutex);
}

void consume_end(struct prodcons* pc) {
    sem_post(pc->mutex);
    sem_post(pc->empty);
}

void semaphore_mutex_lock(sem_t* sem) {
    sem_wait(sem);
}

void semaphore_mutex_unlock(sem_t* sem) {
    sem_post(sem);
}