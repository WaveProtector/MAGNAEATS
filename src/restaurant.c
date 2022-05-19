//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <restaurant.h>
#include <stdio.h>
#include <metime.h>

int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    int processed_ops, i;
    int *pro = &processed_ops;
    struct operation aux_op = {0, 0 ,0, "", 'I', 0, 0, 0}; 
    struct operation* op = &aux_op;

    while (*data->terminate != 1) {
        if(i == data->buffers_size)
            i = 0;

        restaurant_receive_operation(op, rest_id, buffers, data, sems);
        register_rest_time(*op); //regista a instância de tempo em que a operação foi recebida pelo restaurante
                
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
      sem_wait(sems->main_rest->empty);  
      read_main_rest_buffer(buffers->main_rest, rest_id, data->buffers_size, op);
    }

}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter, struct semaphores* sems) {

    op->receiving_rest = rest_id;
    op->status = 'R';
    int i;
    counter++;
    
    *(data->restaurant_stats + (op->id - 1)) += 1;
    sem_wait(sems->main_rest->mutex);
    for(i = 0; i < data->buffers_size; i++) {
        if((data->results[i]).id == op->id)
            data->results[i] = *op;
    }
    sem_post(sems->main_rest->mutex);

}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    sem_post(sems->rest_driv->full);
    
}


