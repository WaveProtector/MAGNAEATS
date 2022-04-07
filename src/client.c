#include "client.h"

int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {
    do {    
        struct operation* op = buffers->driv_cli->buffer;
        client_get_operation(op, client_id, buffers, data);
        if(op->id != -1) {
            int counter = 0;
            client_process_operation(op, client_id, data, counter);
        }
    } while (data->terminate == 0);
    return data->client_stats;
}

void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data) {
    if(data->terminate == 0) {
        read_driver_client_buffer(buffers->driv_cli, client_id, data->buffers_size, op);
        op->requesting_client = client_id;
    }
    return 0;
}

void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter) {
    op->receiving_client = client_id;
    op->status = 'C';
    counter++;
    return 0;
}