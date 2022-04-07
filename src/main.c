#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <process.h>
#include <string.h>

void main_args(int argc, char* argv[], struct main_data* data) {
	data->max_ops = atoi(argv[1]);
	data->buffers_size = atoi(argv[2]);
	data->n_restaurants = atoi(argv[3]);
	data->n_drivers = atoi(argv[4]);
	data->n_clients = atoi(argv[5]);
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

void launch_processes(struct communication_buffers* buffers, struct main_data* data) {

	for (int i = 0; i < data->n_restaurants; i++) {
		*(data->restaurant_pids + i) = launch_restaurant (i + 1, buffers, data);
	}

	for (int i = 0; i < data->n_clients; i++) {
		*(data->client_pids + i) = launch_client (i + 1, buffers, data);
	}

	for (int i = 0; i < data->n_drivers; i ++) {
		*(data->driver_pids + i) = launch_driver (i + 1, buffers, data);
	}

}

void user_interaction(struct communication_buffers* buffers, struct main_data* data) {

    while (*data->terminate != 0) {
		
		char s [] = "";
        int counter = 0;
	    int *c = &counter;

	    printf("Options: \n-request \n-status \n-stop \n-help \nChoose your option: \n");
	    scanf("%s", s);

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
		           "-request -> Type 'request' and press enter to make an order.\n"
			       "-status -> Type 'status' and press enter to check the status of an order.\n"
			       "-stop -> Type 'stop' to finish the program.\n" 
			       "-help -> Type 'help' to read information about your options.\n \n \n \n");
	    }

	}

}

void create_request(int* op_counter, struct communication_buffers* buffers, struct main_data* data) {

    if (*op_counter < data->max_ops) {

	    char s [] = "";
	    char* token;

	    printf("Enter your 'client_number restaurant_number dish': \n");
	    scanf("%s", s);	

	    token = strtok(s, " ");
	    int req_cli = atoi(token);
	    token = strtok(NULL, " ");
	    int req_rest = atoi(token);
	    token = strtok(NULL, " ");
	    char* req_dish = token;

		if (req_cli != 0 && req_rest != 0) {

			struct operation newOne = {*op_counter, req_rest, req_cli, req_dish, 'I', 0, 0, 0};
			struct operation *newPoiter = &newOne;
			write_main_rest_buffer(buffers->main_rest, data->buffers_size, newPoiter);

	    }

		else {
			printf("This restaurant or client number does not exist. You need to try it again. \n");
		}

	}

	else {
		printf("Error: max number of operations reached.");
	}
}

void read_status(struct main_data* data) {

    char s [] = "";

	printf("Enter your 'order_id': \n");
	scanf("%s", s);

	int check = 0;
	for (int i = 0; i < data->buffers_size; i++) {
		if (atoi(s) == (*((data->results) + i)).id) {
			printf("Order ID: %d \n"
				   "Order status: %c \n"
			       "Requesting client ID: %d \n"
				   "Requested restaurant ID: %d \n"
				   "Dish: %s \n"
				   "Received restaurant ID: %d \n"
				   "Received driver ID: %d \n"
				   "Received client ID: %d \n",
				   (*((data->results) + i)).id,
				   (*((data->results) + i)).status,
				   (*((data->results) + i)).requesting_client,
				   (*((data->results) + i)).requested_rest,
				   (*((data->results) + i)).requested_dish,
				   (*((data->results) + i)).receiving_rest,
				   (*((data->results) + i)).receiving_driver,
				   (*((data->results) + i)).receiving_client);
			check += 1;
		}
	}			
	if (check == 0) {
		printf("Error: this order id does not exist.");
	}
}

void stop_execution(struct main_data* data, struct communication_buffers* buffers) {
	*data->terminate = 1;
	wait_processes(data);
	write_statistics(data);
	destroy_memory_buffers(data, buffers);
}

void wait_processes(struct main_data* data) {

	for (int i = 0; i < data->n_restaurants; i++) {
		wait_process(*(data->restaurant_pids + 1));
	}

	for (int i = 0; i < data->n_clients; i++) {
		wait_process(*(data->client_pids + 1));
	}

	for (int i = 0; i < data->n_drivers; i++) {
		wait_process(*(data->driver_pids + 1));
	}

}

void write_statistics(struct main_data* data) {

	int i;

	for(i = 0; i < data->n_restaurants; i++) {
		printf("Restaurante %d: %d operacoes\n", (i+1), data->restaurant_stats[i]);
	}

	printf("\n");

	for(i = 0; i < data->n_drivers; i++) {
		printf("Restaurante %d: %d operacoes\n", (i+1), data->driver_stats[i]);
	}

	printf("\n");

	for(i = 0; i < data->n_clients; i++) {
		printf("Restaurante %d: %d operacoes\n", (i+1), data->client_stats[i]);
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
