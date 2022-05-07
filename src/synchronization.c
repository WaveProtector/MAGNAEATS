#include "synchronization.h"
#include "string.h"
#include "fcntl.h"

sem_t * semaphore_create(char* name, int value) {
    return sem_open(name, O_CREAT, 0666, value); //a professora não deu isto e diz para fazermos com getuid() mas não sei como criar semáforos sem usar o sem_open?
                                                 //então é capaz de estar errado desta forma, apesar de funcionar.
}

void semaphore_destroy(char* name, sem_t* semaphore) {
    sem_close(semaphore);
    sem_destroy(semaphore);
}

void produce_begin(struct prodcons* pc) {
    //TODO
}

void produce_end(struct prodcons* pc) {
    //TODO
}

void consume_begin(struct prodcons* pc) {
    //TODO
}

void consume_end(struct prodcons* pc) {
    //TODO
}

void semaphore_mutex_lock(sem_t* sem) {
    //TODO
}

void semaphore_mutex_unlock(sem_t* sem) {
    //TODO
}