//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <driver.h>
#include <stdio.h>
#include <metime.h>

int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    int processed_ops = 0;;
    int i = 0;
    int *pro = &processed_ops;
    struct operation aux_op = {0, 0 ,0, "", 'I', 0, 0, 0}; 
    struct operation* op = &aux_op;

    while (*data->terminate != 1) {
        if(i == data->buffers_size)
            i = 0;
                
        driver_receive_operation(op, buffers, data, sems); 
        register_driver_time(*op);

        if (op->id > 0 && *data->terminate == 0) {
            driver_process_operation(op, driver_id, data, pro, sems);
            processed_ops++;
            driver_send_answer(op, buffers, data, sems);
        }
        i++;
    }
    
    return processed_ops;
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    if(*data->terminate != 1){
        consume_begin(sems->rest_driv);
        read_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
        consume_end(sems->rest_driv);
    }
}

void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter, struct semaphores* sems) {
    op->receiving_driver = driver_id;
    op->status = 'D';
    int i;
    (*counter)++;
    *(data->driver_stats + (driver_id - 1)) += 1;
    for(i = 0; i < data->buffers_size; i++) {
        if((data->results[i]).id == op->id) {
            semaphore_mutex_lock(sems->results_mutex);
            data->results[i] = *op;
            semaphore_mutex_unlock(sems->results_mutex);
        }
    }
}

void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
        produce_begin(sems->driv_cli);
        write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
        produce_end(sems->driv_cli);
}