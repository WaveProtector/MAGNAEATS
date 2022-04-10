#include "client.h"
#include <stdio.h>

int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {
    int processed_ops, i;
    int *pro = &processed_ops;
    while (*data->terminate != 1) {
            if (i == data->buffers_size)
                i = 0;

            struct operation aux_op = {0, 0 ,0, "", 'I', 0, 0, 0}; 
            struct operation* op = &aux_op;

            client_get_operation(op, client_id, buffers, data);
    

            if (op->id > 0 && *data->terminate == 0) {
                client_process_operation(op, client_id, data, pro);
                processed_ops++;
                op->id = -1;
            }

            i++;

    }
    return processed_ops;
}



void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data) {
    if (*data->terminate != -1)
        read_driver_client_buffer(buffers->driv_cli, client_id, data->buffers_size, op);

}

void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter) {
    op->receiving_client = client_id;
    op->status = 'C';
    int i;
    counter++;
    data->client_stats++;
    for(i = 0; i < data->buffers_size; i++) {
        if((data->results[i]).id == op->id)
            data->results[i] = *op;
    }
}