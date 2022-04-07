#include "driver.h"

int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {
    int id_driver = driver_id;
    int processed_ops = 0;
    int *pro = &processed_ops;

    while (*data->terminate != 1) {

        for(int i = 0; i < (data->buffers_size/sizeof(int)); i++) {
            struct operation* new_op = buffers->main_rest->buffer + i;

            if (buffers->main_rest->ptrs[i] == 1 && (*new_op).id != -1 && data->terminate == 0) {
                driver_receive_operation(new_op, buffers, data); 

                driver_process_operation(new_op, id_driver, data, pro);
                id_driver--;

                driver_send_answer(new_op, buffers, data);
                processed_ops++;
            }
        }
    }
    
    return processed_ops;
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {

    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);

}

void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter) {

    op->receiving_driver = driver_id;
    op->status = 'D';
    int nextOp = *counter++; //incrementar o counter pois vamos adicionar mais uma operação ao conjunto de operações realizadas
    data->results[nextOp] = *op;
    data->driver_pids++;
    data->driver_stats++;
}

void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
        
        write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
}