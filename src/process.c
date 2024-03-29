//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <unistd.h>
#include <stdlib.h>
#include <process.h>
#include <driver.h>
#include <client.h>
#include <restaurant.h>
#include <sys/types.h>
#include <sys/wait.h>


int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {

    int pid = fork();

    if (pid == 0) {
        exit(execute_restaurant(restaurant_id, buffers, data, sems));

    } else {
        return pid;
    }
}

int launch_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {

    int pid = fork();

    if (pid == 0) {
        exit(execute_driver(driver_id, buffers, data, sems));

    } else {
        return pid;
    }
}

int launch_client(int client_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {

    int pid = fork();

    if (pid == 0) {
        exit(execute_client(client_id, buffers, data, sems));

    } else {
        return pid;
    }
}

int wait_process(int process_id) {
    int status = 0;
    int *st = &status;
    waitpid(process_id, st, 0);
    if(WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1;
}

