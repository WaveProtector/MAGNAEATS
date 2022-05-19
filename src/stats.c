//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <stats.h>
#include <stdio.h>
#include <string.h>

void execute_stats(struct main_data* data) {
	FILE *config = fopen("../config.txt", "r");
    char line[100]; //linhas lidas do config.txt
	char file_src[50] = "../";
	char* file_name;
    int count = 0; //count para sabermos quantas linhas já foram lidas
    int lineNumber = 6; //linha em que aparece o nome do ficheiro
	char foundLine = 0; //"booleano" para parar o while se encontrarmos a linha que contem o nome do ficheiro para o stats

	while (foundLine == 0) { //Se a linha não for encontrada continuamos a ler até encontrarmos, isto é, vamos pondo as linhas em "line" até encontrarmos a linha que queremos
		fgets(line, sizeof line, config);
		if (count == lineNumber) {
			file_name = strcat(file_src, line); //para depois criarem um ficheiro fora do src senão os professores ficam putos conosco 
			foundLine++;
			printf("Este é o file name %s", file_name); //só para veres qual é a linha que foi lida, depois podes apagar isto
		} else {
			count++;
		}
	}

    fclose(config);
    
    FILE *stats = fopen(file_name, "w");

    fputs("Process Statistics:\n", stats);
    restaurants_prep_req(data->restaurant_stats, data->restaurant_pids, stats);
    drivers_prep_req(data->driver_stats, data->driver_pids, stats);
    clients_prep_req(data->client_stats, data->client_pids, stats);

    fputs("Request Statistics:\n", stats);
    req_stats(data->results, stats);
    fclose(stats);
}

void restaurants_prep_req(int* restaurant_stats, int *restaurant_pids, FILE *stats) {
    char output[500];
	char rest_id[10];
    char num_stats[10];
    for(int i = 0; i < (sizeof(restaurant_stats)/sizeof(restaurant_stats[0])) - 1; i++) { //AVISO - O '-1' no final daqueles sizeof é capaz de dar problema, se der podem tirar, se não deixem estar
        sprintf(rest_id, " %d ", restaurant_pids[i]);       //passamos de int para string
        sprintf(num_stats, " %d ", restaurant_stats[i]);

        strcat(output, "Restaurant ");		//e fazemos concat de várias strings até termos a string completa
		strcat(output, rest_id);
        strcat(output, " prepared ");
        strcat(output, num_stats);
        strcat(output, " requests!\n");

        fputs(output, stats); //metemos a string no ficheiro e passamos para a próxima se houver
    }
}

void drivers_prep_req(int* driver_stats, int *driver_pids, FILE *stats) {
    char output[500];
	char driver_id[10];
    char num_stats[10];
    for(int i = 0; i < (sizeof(driver_stats)/sizeof(driver_stats[0])) - 1; i++) {
        sprintf(driver_id, " %d ", driver_pids[i]);
        sprintf(num_stats, " %d ", driver_stats[i]);

        strcat(output, "Driver ");
		strcat(output, driver_id);
        strcat(output, " delivered ");
        strcat(output, num_stats);
        strcat(output, " requests!\n");

        fputs(output, stats);
    }
}

void clients_prep_req(int* client_stats, int *client_pids, FILE *stats) {
    char output[500];
	char client_id[10];
    char num_stats[10];
    for(int i = 0; i < (sizeof(client_stats)/sizeof(client_stats[0])) - 1; i++) {
        sprintf(client_id, " %d ", client_pids[i]);
        sprintf(num_stats, " %d ", client_stats[i]);

        strcat(output, "Driver ");
		strcat(output, client_id);
        strcat(output, " delivered ");
        strcat(output, num_stats);
        strcat(output, " requests!\n");

        fputs(output, stats);
    }
}

void req_stats(struct operation* results, FILE *stats) {
    char output[500];
    char result_num[10];
    char rest_id[10];
    char driver_id[10];
    char client_id[10];
    struct timespec total_time;

    for(int i = 0; i < (sizeof(results)/sizeof(results[0])) - 1; i++) {
        sprintf(result_num, " %d\n", i);
        sprintf(rest_id, " %d\n", results[i].receiving_rest);
        sprintf(driver_id, " %d\n", results[i].receiving_driver);
        sprintf(client_id, " %d\n", results[i].receiving_client);

        strcat(output, "Request: ");
        strcat(output, result_num);
        strcat(output, "\n");

        strcat(output, "Status: ");
        strcat(output, results[i].status);
        strcat(output, "\n");

        strcat(output, "Restaurant id: ");
        strcat(output, rest_id);
        strcat(output, "\n");

        strcat(output, "Driver id: ");
        strcat(output, driver_id);
        strcat(output, "\n");

        strcat(output, "Client id: ");
        strcat(output, client_id);
        strcat(output, "\n");

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