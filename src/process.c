#include "process.h"
#include "driver.c"
#include "client.c"
#include "restaurant.c"

int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data) {

    int pid = fork();

    if (pid == 0) {
        exit(execute_restaurant(restaurant_id, buffers, data));

    } else {
        return pid;
    }
}

int launch_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {

    int pid = fork();

    if (pid == 0) {
        exit(execute_driver(driver_id, buffers, data));

    } else {
        return pid;
    }
}

int launch_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {

    int pid = fork();

    if (pid == 0) {
        exit(execute_client(client_id, buffers, data));

    } else {
        return pid;
    }
}

int wait_process(int process_id) {
    return waitpid(process_id); //é suposto fazer assim?
}
