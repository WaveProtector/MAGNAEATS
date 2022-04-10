#include "driver.h"
#include <stdio.h>

int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {
    int processed_ops = 0, i;
    int *pro = &processed_ops;
    struct operation aux_op = {0, 0 ,0, "", 'I', 0, 0, 0}; 
    struct operation* op = &aux_op;

    while (*data->terminate != 1) {
            if(i == data->buffers_size)
                i = 0;
                
            driver_receive_operation(op, buffers, data); 
            if (op->id > 0 && *data->terminate == 0) {
                driver_process_operation(op, driver_id, data, pro);
                processed_ops++;
                driver_send_answer(op, buffers, data);
            }
            i++;
    }
    
    return processed_ops;
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {

    if(*data->terminate != 1)
        read_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);

}

void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter) {

    op->receiving_driver = driver_id;
    op->status = 'D';
    int i;
    (*counter)++;
    *(data->driver_stats + (op->id - 1)) += 1;
    for(i = 0; i < data->buffers_size; i++) {
        if((data->results[i]).id == op->id) {
            data->results[i] = *op;
        }
    }
}

void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
        
        write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
}