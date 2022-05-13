#include "memory.h"
#include "time.h"

//Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
//regista a instância de tempo atual no parâmetro start_time.
void register_start_time(struct operation op);

//Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
//regista a instância de tempo atual no parâmetro rest_time.
void register_rest_time(struct operation op);

//Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
//regista a instância de tempo atual no parâmetro driver_time.
void register_driver_time(struct operation op);

//Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
//regista a instância de tempo atual no parâmetro client_end_time.
void register_client_end_time(struct operation op);