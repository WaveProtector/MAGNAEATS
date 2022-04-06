#include "client.h"

int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {
    int id_client = client_id;
    int processed_ops;
    while (*data->terminate != 1) {

        for(int i = 0; i < (data->buffers_size/sizeof(int)); i++) {
            struct operation* new_op = buffers->driv_cli->buffer + i;

            if (buffers->driv_cli->ptrs[i] == 1 && (*new_op).id != -1 && data->terminate == 0) {
                driver_receive_operation(new_op, buffers, data); 
                
                driver_process_operation(new_op, id_client, data, sizeof(data->results)/sizeof(*new_op));
                id_client--;
                processed_ops++;
            }
        }

    }
}



void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data) {

    read_driver_client_buffer(buffers->driv_cli, client_id, data->buffers_size, op);
    op->requesting_client = client_id;

}

void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter) {
    op->receiving_client = client_id;
    op->status = 'C';
    counter++;
}