#include "restaurant.h"

int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data) {
    do {
        struct operation* op;
        restaurant_receive_operation(op, rest_id, buffers, data);
        if(op->id != -1) {
            int counter = 0;
            restaurant_process_operation(op, rest_id, data, counter);
            restaurant_forward_operation(op, buffers, data);
        }
    } while (data->terminate == 0);
    return data->restaurant_stats;
}

void restaurant_receive_operation(struct operation* op, int rest_id, struct communication_buffers* buffers, struct main_data* data) {
    if(data->terminate == 0) {
        read_main_rest_buffer(buffers->main_rest, rest_id, data->buffers_size, op);
        op->requested_rest = rest_id;
    }
    return 0;
}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter) {
    op->receiving_rest = rest_id;
    op->status = 'R';
    counter++;
    return 0;
}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    return 0;
}

