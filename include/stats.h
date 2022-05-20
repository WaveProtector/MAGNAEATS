//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <main.h>
#include <stdio.h>

/* Função que escreve as estatísticas finais do magnaeats, incluindo as
* estatísticas de todos os processos e de todos os pedidos, para um 
* ficheiro .txt com o argumento 'statistics_filename' passado no
* ficheiro config.txt
*/
void execute_stats(struct main_data* data);

/* Função que recebe o nº de operações encaminhadas por cada restaurante e
* os process ids dos restaurantes, e regista strings no ficheiro stats do tipo 
* 'Restaurant id prepared n requests!', onde id é o id do restaurante e 
* n é o nº de operações encaminhados pelo restaurante com esse id.
*/
void restaurants_prep_req(int* restaurant_stats, int *restaurant_pids, FILE *stats);

/* Função que recebe o nº de operações respondidas por cada motorista e
* os process ids dos motoristas, e regista strings no ficheiro stats do tipo 
* 'Driver id delivered n requests!', onde id é o id do motorista e 
* n é o nº de operações respondidas pelo motorista com esse id.
*/
void drivers_prep_req(int* driver_stats, int *driver_pids, FILE *stats);

/* Função que recebe o nº de operações recebidas por cada cliente e
* os process ids dos clientes, e regista strings no ficheiro stats do tipo 
* 'Client id received n requests!', onde id é o id do cliente e 
* n é o nº de operações recebidas pelo cliente com esse id.
*/
void clients_prep_req(int* client_stats, int *client_pids, FILE *stats);

/* Função que recebe o histórico de operações executadas e regista
* uma string com as informações de cada operação no ficheiro stats.
*/
void req_stats(struct operation* results, FILE *stats);