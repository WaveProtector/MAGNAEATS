#include "stats.h";
#include "stdio.h";
#include "string.h";

void execute_stats(struct main_data* data) {
    FILE *config = fopen("config.txt", "r");
    char* line;
    int count = 0;
    int lineNumber = 6;
    char* file_name;

    while (fgets(line, sizeof line, config) != NULL) {
        if(count == lineNumber) {
            file_name = line;
        } else {
            count++;
        }
    }
    fclose(config);
    
    FILE *stats = fopen(file_name, "w");
    count = 0;
    char* res_output = restaurants_prep_req(data->restaurant_stats, data->restaurant_pids);
    while(count < sizeof(res_output)/sizeof(res_output)) { //tanto faz meter size dos restaurantes ou clientes ou drivers, pois vamos sempre ter o mesmo número
        fputs("Process Statistics:\n", stats);
        fputs(res_output[count], stats);
        fputs(drivers_prep_req(data->driver_stats, data->driver_pids)[count], stats);
        fputs(clients_prep_req(data->client_stats, data->client_pids)[count], stats);
    }
    fputs("Request Statistics:\n", stats);
    fputs(req_stats(data->results), stats);
    fclose(stats);
}

char* restaurants_prep_req(int* restaurant_stats, int *restaurant_pids) {
    char* output[(sizeof(restaurant_stats)/sizeof(restaurant_stats[0])) * 2]; //Este é um array de strings, assim fica mais fácil fazer cada linha no ciclo for
    char* rest_id;
    char* num_stats;
    for(int i = 0; i < sizeof(restaurant_stats)/sizeof(restaurant_stats[0]); i++) {
        sprintf(rest_id, " %d ", restaurant_pids[i]);       //passamos de int para string
        sprintf(num_stats, " %d ", restaurant_stats[i]);

        output[i] = strcat("Restaurant ", rest_id);         //e fazemos concat de várias strings até termos a string completa
        output[i] = strcat(output[i], " prepared ");
        output[i] = strcat(output[i], num_stats);
        output[i] = strcat(output[i], " requests!");
    }
    return output; //retornamos o array de strings
}

char* drivers_prep_req(int* driver_stats, int *driver_pids) {
    char* output[(sizeof(driver_stats)/sizeof(driver_stats[0])) * 2];
    char* driver_id;
    char* num_stats;
    for(int i = 0; i < sizeof(driver_stats)/sizeof(driver_stats[0]); i++) {
        sprintf(driver_id, " %d ", driver_pids[i]);
        sprintf(num_stats, " %d ", driver_stats[i]);
        output[i] = strcat("Driver ", driver_id);
        output[i] = strcat(output[i], " delivered ");
        output[i] = strcat(output[i], num_stats);
        output[i] = strcat(output[i], " requests!");
    }
    return output;
}

char* clients_prep_req(int* client_stats, int *client_pids) {
    char* output[(sizeof(client_stats)/sizeof(client_stats[0])) * 2];
    char* client_id;
    char* num_stats;
    for(int i = 0; i < sizeof(client_stats)/sizeof(client_stats[0]); i++) {
        sprintf(client_id, " %d ", client_pids[i]);
        sprintf(num_stats, " %d ", client_stats[i]);
        output[i] = strcat("Client ", client_id);
        output[i] = strcat(output[i], " received ");
        output[i] = strcat(output[i], num_stats);
        output[i] = strcat(output[i], " requests!");
    }
    return output;
}

char* req_stats(struct operation* results) {
    char* output[(sizeof(results)/sizeof(results[0])) * 2];
    char* result_num;
    char* rest_id;
    char* driver_id;
    char* client_id;
    struct timespec total_time;

    for(int i = 0; i < sizeof(results)/sizeof(results[0]); i++) {
        sprintf(result_num, " %d\n", i);
        sprintf(rest_id, " %d\n", results[i].receiving_rest);
        sprintf(driver_id, " %d\n", results[i].receiving_driver);
        sprintf(client_id, " %d\n", results[i].receiving_client);

        output[i] = strcat("Request: ", result_num);

        output[i] = strcat(output, "Status: ");
        output[i] = strcat(output, results[i].status);

        output[i] = strcat(output, "Restaurant id: ");
        output[i] = strcat(output, rest_id);

        output[i] = strcat(output, "Driver id: ");
        output[i] = strcat(output, driver_id);

        output[i] = strcat(output, "Client id: ");
        output[i] = strcat(output, client_id);

        output[i] = strcat(output, "Created: ");
        output[i] = strcat(output, timespec_to_date(results[i].start_time));
        output[i] = strcat(output, "\n");

        output[i] = strcat(output, "Restaurant time: ");
        output[i] = strcat(output, timespec_to_date(results[i].rest_time));
        output[i] = strcat(output, "\n");

        output[i] = strcat(output, "Driver time: ");
        output[i] = strcat(output, timespec_to_date(results[i].driver_time));
        output[i] = strcat(output, "\n");

        output[i] = strcat(output, "Client time (end): ");
        output[i] = strcat(output, timespec_to_date(results[i].client_end_time));
        output[i] = strcat(output, "\n");

        total_time.tv_sec = results[i].client_end_time.tv_sec - results[i].start_time.tv_sec;
        total_time.tv_nsec = results[i].client_end_time.tv_nsec - results[i].start_time.tv_nsec;
        output[i] = strcat(output, timespec_to_seconds(total_time));
        output[i] = strcat(output, "\n");
    }
}