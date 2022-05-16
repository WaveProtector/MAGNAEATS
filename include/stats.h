#include "main.h"
#include "metime.h"

/* Função que escreve as estatísticas finais do magnaeats, incluindo as
* estatísticas de todos os processos e de todos os pedidos, para um 
* ficheiro .txt com o argumento 'statistics_filename' passado no
* ficheiro config.txt
*/
void execute_stats(struct main_data* data);

/* Função que recebe o nº de operações encaminhadas por cada restaurante e
* os process ids dos restaurantes, e devolve uma string do tipo 
* 'Restaurant id prepared n requests!', onde id é o id do restaurante e 
* n é o nº de operações encaminhados pelo restaurante com esse id.
*/
char* restaurants_prep_req(int* restaurant_stats, int *restaurant_pids);

/* Função que recebe o nº de operações respondidas por cada motorista e
* os process ids dos motoristas, e devolve uma string do tipo 
* 'Driver id delivered n requests!', onde id é o id do motorista e 
* n é o nº de operações respondidas pelo motorista com esse id.
*/
char* drivers_prep_req(int* driver_stats, int *driver_pids);

/* Função que recebe o nº de operações recebidas por cada cliente e
* os process ids dos clientes, e devolve uma string do tipo 
* 'Client id received n requests!', onde id é o id do cliente e 
* n é o nº de operações recebidas pelo cliente com esse id.
*/
char* clients_prep_req(int* client_stats, int *client_pids);

/* Função que recebe o histórico de operações executadas e devolve
* uma string com as informações de cada operação
*/
char* req_stats(struct operation* results);