//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <memory.h>
#include <time.h>

/* Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
* regista a instância de tempo atual no parâmetro start_time.
*/
void register_start_time(struct operation *op);

/* Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
* regista a instância de tempo atual no parâmetro rest_time.
*/
void register_rest_time(struct operation *op);

/* Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
* regista a instância de tempo atual no parâmetro driver_time.
*/
void register_driver_time(struct operation *op);

/* Função que recebe uma operação e regista a instância de tempo em que foi criada, neste caso,
* regista a instância de tempo atual no parâmetro client_end_time.
*/
void register_client_end_time(struct operation *op);

/* Função que recebe uma instância de tempo e retorna uma string do tipo 
* 'ano-mês-dia hora-minutos-segundos.milisegundos'
*/
char* timespec_to_date(struct timespec time);

/* Função que recebe uma instância de tempo e retorna uma string do tipo
* 'segundos.milisegundos
*/
char* timespec_to_seconds(struct timespec time);