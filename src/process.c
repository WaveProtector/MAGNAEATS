#include "process.h"

int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data) {
    int pid = fork();

    if (pid == 0) {
        //tf como é que se chama a execute_restaurant??? acho que temos de adicionar nós, nesse caso é 
        //preciso rever o driver.c e outros que não usem funções auxiliares da memory.c

    } else {

    }

    return pid;
}

int launch_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {

    return 0;
}

int launch_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {

    return 0;
}

int wait_process(int process_id) {

    return 0;
}
