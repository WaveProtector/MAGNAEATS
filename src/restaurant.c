//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <restaurant.h>
#include <stdio.h>
#include <metime.h>

int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    int processed_ops = 0; 
    int i = 0;
    int *pro = &processed_ops;
    struct operation aux_op = {0, 0 ,0, "", 'I', 0, 0, 0}; 
    struct operation* op = &aux_op;

    while (*data->terminate != 1) {
        if(i == data->buffers_size)
            i = 0;

        restaurant_receive_operation(op, rest_id, buffers, data, sems);
        register_rest_time(op);
                
        if ((op->id) > 0 && *data->terminate == 0) {
            restaurant_process_operation(op, rest_id, data, pro, sems);
            processed_ops++;
            restaurant_forward_operation(op, buffers, data, sems);
            op->id = -1;
        }
        i++;     
    }
    
    return processed_ops;
}

void restaurant_receive_operation(struct operation* op, int rest_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    if(*data->terminate != 1) {
      consume_begin(sems->main_rest);  
      read_main_rest_buffer(buffers->main_rest, rest_id, data->buffers_size, op);
      consume_end(sems->main_rest);
    }

}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter, struct semaphores* sems) {

    op->receiving_rest = rest_id;
    op->status = 'R';
    int i;
    counter++;
    
    data->restaurant_stats[rest_id - 1] += 1;
    for(i = 0; i < data->buffers_size; i++) {
        if((data->results[i]).id == op->id) {
            semaphore_mutex_lock(sems->results_mutex);
            data->results[i] = *op;
            semaphore_mutex_unlock(sems->results_mutex);

        }
    }

}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    produce_begin(sems->rest_driv);
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    produce_end(sems->rest_driv);
    
}


