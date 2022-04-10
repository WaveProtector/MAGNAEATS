#include "restaurant.h"
#include <stdio.h>

int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data) {
    
    
    int processed_ops, i;
    int *pro = &processed_ops;
    struct operation aux_op = {0, 0 ,0, "", 'I', 0, 0, 0}; 
    struct operation* op = &aux_op;

    while (*data->terminate != 1) {
        if(i == data->buffers_size)
            i = 0;

        restaurant_receive_operation(op, rest_id, buffers, data);
                
        if ((op->id) > 0 && *data->terminate == 0) {
            
            restaurant_process_operation(op, rest_id, data, pro);
            processed_ops++;
            restaurant_forward_operation(op, buffers, data);
            op->id = -1;
        }

        i++;
                
    }
    
    return processed_ops;

}

void restaurant_receive_operation(struct operation* op, int rest_id, struct communication_buffers* buffers, struct main_data* data) {
    if(*data->terminate != 1) {
      read_main_rest_buffer(buffers->main_rest, rest_id, data->buffers_size, op);
    }

}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter) {

    op->receiving_rest = rest_id;
    op->status = 'R';
    int i;
    counter++;
    data->restaurant_stats++;
    for(i = 0; i < data->buffers_size; i++) {
        if((data->results[i]).id == op->id)
            data->results[i] = *op;
    }

}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    
}


