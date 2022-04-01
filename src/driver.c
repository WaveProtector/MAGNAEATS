#include "driver.h"

int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {
    int id_driver = driver_id;
    int processed_ops;

    while (data->terminate != 1) {

        for(int i = 0; i < (sizeof(buffers->main_rest->ptrs)/sizeof(buffers->main_rest->ptrs[0])); i++) {
            struct operation new_op = buffers->main_rest->buffer[i];

            if (buffers->main_rest->ptrs[i] == 1 && new_op.id != -1 && data->terminate == 0) {
                driver_receive_operation(&new_op, buffers, data); //podemos estar a usar mal o &

                driver_process_operation(&new_op, id_driver, data, sizeof(data->results));
                id_driver--;

                driver_send_answer(&new_op, buffers, data);
                processed_ops++;
            }
        }
    }
    
    return processed_ops; //mas cuidado para mudar isto que esta função deve retornar algo
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {

    if (data->terminate == 1) {
        return 0;

    } else {
        write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    }

    return 0;
}

void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter) {

    op->receiving_driver = driver_id;
    op->status = 'D';
    int nextOp = counter++; //incrementar o counter pois vamos adicionar mais uma operação ao conjunto de operações realizadas
    data->results[nextOp] = *op;
    data->driver_pids++;
    data->driver_stats++;

    return 0;
}

void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {

    if(data->terminate == 1) {
        return 0;

    } else {
        int foundEmpty = 0; //funciona como um booleano
        for (int i = 0; i < (sizeof(buffers->driv_cli->ptrs)/sizeof(buffers->driv_cli->ptrs[0])) && foundEmpty == 0; i++) {
            if (buffers->driv_cli->ptrs[i] == 0) {  //fazemos um ciclo for até encontrarmos uma posição vazia no buffer.
                foundEmpty++;                       //Ao encontrar a posição vazia incrementamos o booleano para interromper
                buffers->driv_cli->buffer[i] = *op; //o ciclo for.
            }
        }
        write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
    }

    return 0; //pode haver problema aqui porque podemos não ter retirado a op de algum buffer!!!
}