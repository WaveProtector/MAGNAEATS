#include "restaurant.h"

int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data) {


    int id_rest = rest_id;
    int processed_ops;
    int *pro = &processed_ops;

    while (*data->terminate != 1) {

        for(int i = 0; i < (data->buffers_size/sizeof(int)); i++) {
                struct operation* new_op = buffers->rest_driv->buffer + i;

                if ((*new_op).id != -1 && data->terminate == 0) {
                    restaurant_receive_operation(new_op, id_rest, buffers, data); 

                    restaurant_process_operation(new_op, id_rest, data, pro);
                    id_rest--;
                    processed_ops++;
                }
            }
    }

    return processed_ops;

}

void restaurant_receive_operation(struct operation* op, int rest_id, struct communication_buffers* buffers, struct main_data* data) {

    read_main_rest_buffer(buffers->main_rest, rest_id, data->buffers_size, op);
    op->requested_rest = rest_id;

}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter) {

    op->receiving_rest = rest_id;
    op->status = 'R';
    counter++;

}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
}


