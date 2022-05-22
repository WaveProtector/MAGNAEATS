//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <process.h>
#include <string.h>
#include <ctype.h>
#include <metime.h>
#include <unistd.h>
#include <log.h>

int isnumber(char *arg) {
	int i;
	for(i = 0; i < strlen(arg); i++) {
		if (isdigit(arg[i]) == 0) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[]) {
//init data structures
	struct main_data* data = create_dynamic_memory(sizeof(struct
	main_data));
	struct communication_buffers* buffers = create_dynamic_memory(sizeof(struct communication_buffers));
	buffers->main_rest = create_dynamic_memory(sizeof(struct
	rnd_access_buffer));
	buffers->rest_driv = create_dynamic_memory(sizeof(struct
	circular_buffer));
	buffers->driv_cli = create_dynamic_memory(sizeof(struct
	rnd_access_buffer));
// init semaphore data structure
	struct semaphores* sems = create_dynamic_memory(sizeof(struct
	semaphores));
	sems->main_rest = create_dynamic_memory(sizeof(struct prodcons));
	sems->rest_driv = create_dynamic_memory(sizeof(struct prodcons));
	sems->driv_cli = create_dynamic_memory(sizeof(struct prodcons));
//execute main code
    struct config conf = {"","",0};
	struct config *cf = &conf;	
	get_config_params(data, cf);
	create_dynamic_memory_buffers(data);
	create_shared_memory_buffers(data, buffers);
	create_semaphores(data, sems);
	launch_processes(buffers, data, sems);
	user_interaction(buffers, data, sems);
	destroy_memory_buffers(data, buffers);
//release memory before terminating
	destroy_dynamic_memory(data);
	destroy_dynamic_memory(buffers->main_rest);
	destroy_dynamic_memory(buffers->rest_driv);
	destroy_dynamic_memory(buffers->driv_cli);
	destroy_dynamic_memory(buffers);
	destroy_dynamic_memory(sems->main_rest);
	destroy_dynamic_memory(sems->rest_driv);
	destroy_dynamic_memory(sems->driv_cli);
	destroy_dynamic_memory(sems);
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
	data->results = create_shared_memory(STR_SHM_RESULTS, data->max_ops);
	data->terminate = create_shared_memory(STR_SHM_TERMINATE, sizeof(int));

}

void launch_processes(struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {

	for (int i = 0; i < data->n_restaurants; i++) {
		*(data->restaurant_pids + i) = launch_restaurant (i + 1, buffers, data, sems);
	}

	for (int i = 0; i < data->n_clients; i++) {
		*(data->client_pids + i) = launch_client (i + 1, buffers, data, sems);
	}

	for (int i = 0; i < data->n_drivers; i ++) {
		*(data->driver_pids + i) = launch_driver (i + 1, buffers, data, sems);
	}

}

void user_interaction(struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {

	int counter = 0;

    while (*data->terminate == 0) {
		
		char s [100];
	    int *c = &counter;

	    printf("Options: \n \n-request \n-status \n-stop \n-help \n \nChoose your option: \n");
	    scanf("%s", s);

	    if (strcmp(s, "request") == 0) {
			create_request(c, buffers, data, sems);
		}

	    else if (strcmp(s, "status") == 0) {
			read_status(data, sems);
	    }

	    else if (strcmp(s, "stop") == 0) {
		    stop_execution(data, sems);
	    }

	    else if (strcmp(s, "help") == 0) {
			struct timespec time;
			clock_gettime(CLOCK_REALTIME, &time);
			regista_log("log.txt", "help", 0, time);
		    printf("You have 4 options to choose: \n"
		           "-request -> Type 'request' and press enter to make an order.\n"
			       "-status id -> Type 'status' and press enter to check the status of an order.\n"
			       "-stop -> Type 'stop' and press enter to finish the program.\n" 
			       "-help -> Type 'help' and press enter to read information about your options.\n \n");
	    }
		else {
			printf("Type 'help' and press enter to read information about your options. \n");
		}

	}

}

void create_request(int* op_counter, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {

    if (*op_counter < data->max_ops) {

	    char dish[100], c;
		int req_cli;
		int req_rest;
		int len = 0;

	    printf("Enter your 'client_number restaurant_number dish': \n");
	    scanf("%d %d %c", &req_cli, &req_rest, dish);	
		

		if (req_cli != 0 && req_rest != 0 && req_cli <= data->n_clients && req_rest <= data->n_restaurants) { 
			(*op_counter)++;
			struct operation newOne = {*op_counter, req_rest, req_cli, dish, 'I', 0, 0, 0};
			register_start_time(newOne); //regista a instância de tempo em que a operação foi criada
			struct timespec time;
			clock_gettime(CLOCK_REALTIME, &time);
			regista_log("log.txt", "request", 0, time);
			struct operation *newPoiter = &newOne;
			produce_begin(sems->main_rest);
			write_main_rest_buffer(buffers->main_rest, data->buffers_size, newPoiter);
			data->results[*op_counter - 1] = newOne;
			produce_end(sems->main_rest);
			printf("Your order ID: %d \n \n", *op_counter);
	    }

		else {
			printf("This restaurant or client number does not exist. You need to try it again. \n");
		}

	}

	else {
		printf("Error: max number of operations reached.");
	}
}

void read_status(struct main_data* data, struct semaphores* sems) {

    int c;

	printf("Enter your 'order_id': \n");
	scanf("%d", &c);

	int check = 0; //serve como booleano
	for (int i = 0; i < data->buffers_size && c > 0; i++) {
		struct operation new = *((data->results) + i);
		if (c == (*((data->results) + i)).id) {
			struct timespec time;
			clock_gettime(CLOCK_REALTIME, &time);
			regista_log("log.txt", "status", c, time);
			printf("Order ID: %d \n"
				   "Order status: %c \n"
			       "Requesting client ID: %d \n"
				   "Requested restaurant ID: %d \n"
				   "Dish: %s \n"
				   "Received restaurant ID: %d \n"
				   "Received driver ID: %d \n"
				   "Received client ID: %d \n \n",
				   new.id,
				   new.status,
				   new.requesting_client,
				   new.requested_rest,
				   new.requested_dish,
				   new.receiving_rest,
				   new.receiving_driver,
				   new.receiving_client);
			check ++;
		}
	}			
	if (check == 0) {
		printf("Error: this order id does not exist. \n");
	}
}

void stop_execution(struct main_data* data, struct semaphores* sems) {
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	regista_log("log.txt", "stop", 0, time);
	*data->terminate = 1;
	wakeup_processes(data, sems);
	wait_processes(data);
	write_statistics(data);
	destroy_semaphores(sems);
}

void wait_processes(struct main_data* data) {

	for (int i = 0; i < data->n_restaurants; i++) {
		wait_process(*(data->restaurant_pids + i));
	}

	for (int i = 0; i < data->n_clients; i++) {
		wait_process(*(data->client_pids + i));
	}

	for (int i = 0; i < data->n_drivers; i++) {
		wait_process(*(data->driver_pids + i));
	}

}

void write_statistics(struct main_data* data) {

	int i;

	for(i = 0; i < data->n_restaurants; i++) {
		printf("Restaurante %d: %d operacoes\n", (i+1), *(data->restaurant_stats + i));
	}

	printf("\n");

	for(i = 0; i < data->n_drivers; i++) {
		printf("Motorista %d: %d operacoes\n", (i+1), *(data->driver_stats + i));
	}

	printf("\n");

	for(i = 0; i < data->n_clients; i++) {
		printf("Cliente %d: %d operacoes\n", (i+1), *(data->client_stats + i));
	}

}

void destroy_memory_buffers(struct main_data* data, struct communication_buffers* buffers) {
	destroy_dynamic_memory(data->restaurant_pids);
	destroy_dynamic_memory(data->restaurant_stats);
	destroy_dynamic_memory(data->client_pids);
	destroy_dynamic_memory(data->client_stats);
	destroy_dynamic_memory(data->driver_pids);
	destroy_dynamic_memory(data->driver_stats);
	
	destroy_shared_memory(STR_SHM_MAIN_REST_BUFFER, buffers->main_rest->buffer, data->buffers_size);
	destroy_shared_memory(STR_SHM_MAIN_REST_PTR, buffers->main_rest->ptrs, data->buffers_size);
	destroy_shared_memory(STR_SHM_REST_DRIVER_BUFFER, buffers->rest_driv->buffer, data->buffers_size);
	destroy_shared_memory(STR_SHM_REST_DRIVER_PTR, buffers->rest_driv->ptrs, data->buffers_size);
	destroy_shared_memory(STR_SHM_DRIVER_CLIENT_BUFFER, buffers->driv_cli->buffer, data->buffers_size);
	destroy_shared_memory(STR_SHM_DRIVER_CLIENT_PTR, buffers->driv_cli->ptrs, data->buffers_size);
	destroy_shared_memory(STR_SHM_RESULTS, data->results, data->max_ops);
	destroy_shared_memory(STR_SHM_TERMINATE, data->terminate, sizeof(int));
	
}

void create_semaphores(struct main_data* data, struct semaphores* sems) {
	sems->main_rest->full = semaphore_create(STR_SEM_MAIN_REST_FULL, 0);
	sems->main_rest->empty = semaphore_create(STR_SEM_MAIN_REST_EMPTY, data->buffers_size);
	sems->main_rest->mutex = semaphore_create(STR_SEM_MAIN_REST_MUTEX , 1);
	sems->rest_driv->full = semaphore_create(STR_SEM_REST_DRIV_FULL, 0);
	sems->rest_driv->empty = semaphore_create(STR_SEM_REST_DRIV_EMPTY, data->buffers_size);
	sems->rest_driv->mutex = semaphore_create(STR_SEM_REST_DRIV_MUTEX, 1);
	sems->driv_cli->full = semaphore_create(STR_SEM_DRIV_CLI_FULL, 0);
	sems->driv_cli->empty = semaphore_create(STR_SEM_DRIV_CLI_EMPTY, data->buffers_size);
	sems->driv_cli->mutex = semaphore_create(STR_SEM_DRIV_CLI_MUTEX, 1);
	sems->results_mutex = semaphore_create (STR_SEM_RESULTS_MUTEX, 1);
}

void wakeup_processes(struct main_data* data, struct semaphores* sems) {

	for(int i = 0; i < data->max_ops; i++) {
		produce_end(sems->main_rest);
		produce_end(sems->rest_driv);
		produce_end(sems->driv_cli);
		
	}
	
}

void destroy_semaphores(struct semaphores* sems) {
	semaphore_destroy(STR_SEM_MAIN_REST_FULL, sems->main_rest->full);
	semaphore_destroy(STR_SEM_MAIN_REST_EMPTY, sems->main_rest->empty);
	semaphore_destroy(STR_SEM_MAIN_REST_MUTEX, sems->main_rest->mutex);
	semaphore_destroy(STR_SEM_REST_DRIV_FULL, sems->rest_driv->full);
	semaphore_destroy(STR_SEM_REST_DRIV_EMPTY, sems->rest_driv->empty);
	semaphore_destroy(STR_SEM_REST_DRIV_MUTEX, sems->rest_driv->mutex);
	semaphore_destroy(STR_SEM_DRIV_CLI_FULL, sems->driv_cli->full);
	semaphore_destroy(STR_SEM_DRIV_CLI_EMPTY, sems->driv_cli->empty);
	semaphore_destroy(STR_SEM_DRIV_CLI_MUTEX, sems->driv_cli->mutex);
	semaphore_destroy(STR_SEM_RESULTS_MUTEX, sems->results_mutex);
}
