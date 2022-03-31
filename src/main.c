#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <process.h>

void main_args(int argc, char* argv[], struct main_data* data) {
    strcpy(data->max_ops, argv[1]);
    strcpy(data->buffers_size, argv[2]);
    strcpy(data->n_restaurants, argv[3]);
    strcpy(data->n_drivers, argv[4]);
    strcpy(data->n_clients, argv[5]);
}

void create_dynamic_memory_buffers(struct main_data* data) {
	data->restaurant_pids = create_dynamic_memory(data->n_restaurants);
	data->restaurant_stats = create_dynamic_memory(data->n_restaurants);
	data->driver_pids = create_dynamic_memory(data->n_drivers);
	data->driver_stats = create_dynamic_memory(data->n_drivers);
	data->client_pids = create_dynamic_memory(data->n_clients);
	data->client_stats = create_dynamic_memory(data->n_clients);
}

void create_shared_memory_buffers(struct main_data* data, struct communication_buffers* buffers) {

    buffers->main_rest->buffer = create_shared_memory(STR_SHM_MAIN_REST_BUFFER, data->buffers_size);
	buffers->main_rest->ptrs = create_shared_memory(STR_SHM_MAIN_REST_PTR, data->buffers_size);
	buffers->rest_driv->buffer = create_shared_memory(STR_SHM_REST_DRIVER_BUFFER, data->buffers_size);
	buffers->rest_driv->ptrs = create_shared_memory(STR_SHM_REST_DRIVER_PTR, data->buffers_size);
	buffers->driv_cli->buffer = create_shared_memory(STR_SHM_DRIVER_CLIENT_BUFFER, data->buffers_size);
	buffers->driv_cli->ptrs = create_shared_memory(STR_SHM_DRIVER_CLIENT_PTR, data->buffers_size);
	data->results = create_shared_memorySTR_SHM_RESULTS(STR_SHM_RESULTS, data->max_ops);
	data->terminate = create_shared_memory(STR_SHM_TERMINATE, sizeof(int));

}

void launch_processes(struct communication_buffers* buffers, struct main_data* data) {

	for (int i = 0; i < data->n_restaurants; i++) {
		data->restaurant_pids[i] = launch_restaurant (i, buffers, data);
	}

	for (int i = 0; i < data->n_clients; i++) {
		data->client_pids[i] = launch_client (i, buffers, data);
	}

	for (int i = 0; i < data->n_drivers; i ++) {
		data->driver_pids[i] = launch_driver (i, buffers, data);
	}

}

void user_interaction(struct communication_buffers* buffers, struct main_data* data) {

    while (*data->terminate != 0) {
		
		char s [] = "";
        int counter = 0;
	    int *c = &counter;

	    printf("Options: \n-request \n-status \n-stop \n-help \nChoose your option: \n");
	    scanf('%s', s);

	    if (strcmp(s, "request") == 0) {
		    create_request(c, buffers, data);
	    }

	    else if (strcmp(s, "status") == 0) {
		    read_status(data);
	    }

	    else if (strcmp(s, "stop") == 0) {
		    stop_execution(data, buffers);
	    }

	    else if (strcmp(s, "help") == 0) {
		    printf("You have 4 options to choose: \n"
		           "-request -> Type 'request client_number restaurant_number dish' and press enter to make an order.\n"
			       "-status -> Type 'status order_id' and press enter to check the status of an order\n"
			       "-stop -> Type 'stop' to finish the program.\n" 
			       "-help -> Type 'help' to read information about your options.\n \n \n \n");
	    }

	}

}

/* Se o limite de operações ainda não tiver sido atingido, cria uma nova
* operação identificada pelo valor atual de op_counter e com os dados passados em
* argumento, escrevendo a mesma no buffer de memória partilhada entre main e restaurantes.
* Imprime o id da operação e incrementa o contador de operações op_counter.
*/
void create_request(int* op_counter, struct communication_buffers* buffers, struct main_data* data) {

	if (*op_counter < data->max_ops) {
		
	}
}

/* Função que lê um id de operação do utilizador e verifica se a mesma
* é valida. Em caso afirmativo,
* imprime informação da mesma, nomeadamente o seu estado, o id do cliente
* que fez o pedido, o id do restaurante requisitado, o nome do prato pedido
* e os ids do restaurante, motorista, e cliente que a receberam e processaram.
*/
void read_status(struct main_data* data);

/* Função que termina a execução do programa MAGNAEATS. Deve começar por 
* afetar a flag data->terminate com o valor 1. De seguida, e por esta
* ordem, deve esperar que os processos filho terminem, deve escrever as
* estatisticas finais do programa, e por fim libertar
* as zonas de memória partilhada e dinâmica previamente 
* reservadas. Para tal, pode usar as outras funções auxiliares do main.h.
*/
void stop_execution(struct main_data* data, struct communication_buffers* buffers);

/* Função que espera que todos os processos previamente iniciados terminem,
* incluindo restaurantes, motoristas e clientes. Para tal, pode usar a função 
* wait_process do process.h.
*/
void wait_processes(struct main_data* data);

/* Função que imprime as estatisticas finais do MAGNAEATS, nomeadamente quantas
* operações foram processadas por cada restaurante, motorista e cliente.
*/
void write_statistics(struct main_data* data);

/* Função que liberta todos os buffers de memória dinâmica e partilhada previamente
* reservados na estrutura data.
*/
void destroy_memory_buffers(struct main_data* data, struct communication_buffers* buffers);

