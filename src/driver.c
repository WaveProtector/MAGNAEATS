#include "driver.h"

int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {
    //TODO
    return 0; //mas cuidado para mudar isto que esta função deve retornar algo
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data) {

    if (data->terminate == 1) {
        return 0;

    } else {
        //retiramos o pointer in do buffer circular para saber onde é que se vai escrever no buffer
        int in = buffers->rest_driv->ptrs->in;
        int out = buffers->rest_driv->ptrs->out;

        //colocar a operação no buffer
        buffers->rest_driv->buffer[in] = *op;

        //atualizamos o pointer in pois o espaço em que escrevemos já está ocupado
        buffers->rest_driv->ptrs->in = in + 1;

        //tratamos do caso em que o out dá a "volta completa" ao buffer circular e chega ao in
        if (in == out)
            buffers->rest_driv->ptrs->out = out + 1;
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
    }

    return 0;
}