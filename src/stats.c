// Projeto - 2ª fase realizado pelo grupo 21:
// João Assis, fc56325
// José Brás, fc55449
// Ricardo Mateus, fc56366

#include <stats.h>
#include <stdio.h>
#include <string.h>
#include <metime.h>
#include <stdlib.h>

void execute_stats(struct main_data *data)
{
    FILE *config = fopen("config.txt", "r");
    char line[64];
    char *file_name;
    int count = 0;
    int lineNumber = 6;
    char foundLine = 0;

    while (foundLine == 0)
    {
        fgets(line, sizeof line, config);
        if (count == lineNumber)
        {
            file_name = line;
            foundLine++;
        }
        else
        {
            count++;
        }
    }

    fclose(config);

    FILE *stats = fopen(file_name, "w");
    fputs("Process Statistics:\n", stats);
    restaurants_prep_req(data->restaurant_stats, data->n_restaurants, stats);
    drivers_prep_req(data->driver_stats, data->n_drivers, stats);
    clients_prep_req(data->client_stats, data->n_clients, stats);
    fputs("\nRequest Statistics:\n", stats);
    req_stats(data->results, stats);
    fclose(stats);
}

void restaurants_prep_req(int *restaurant_stats, int n_restaurants, FILE *stats)
{
    for (int i = 0; i < n_restaurants; i++)
    {
        fprintf(stats, "    Restaurant %d prepared %d requests!\n", i, restaurant_stats[i]);
    }
}

void drivers_prep_req(int *driver_stats, int n_drivers, FILE *stats)
{
    for (int i = 0; i < n_drivers; i++)
    {
        fprintf(stats, "    Driver %d delivered %d requests!\n", i, driver_stats[i]);
    }
}

void clients_prep_req(int *client_stats, int n_clients, FILE *stats)
{
    for (int i = 0; i < n_clients; i++)
    {
        fprintf(stats, "    Client %d received %d requests!\n", i, client_stats[i]);
    }
}

void req_stats(struct operation *results, FILE *stats)
{
    struct timespec total_time;

    for (int i = 0; i < (sizeof(&results) / sizeof(results[0])); i++)
    {
             total_time.tv_sec = results[i].client_end_time.tv_sec - results[i].start_time.tv_sec;
            total_time.tv_nsec = results[i].client_end_time.tv_nsec - results[i].start_time.tv_nsec;       
            fprintf(stats, "    Request %d\n    Status %d\n     Restaurant id: %d\n     Driver id: %d\n Client id: %d\n",
                    results[i].id,
                    results[i].status,
                    results[i].receiving_rest,
                    results[i].receiving_driver,
                    results[i].receiving_client); 
            fprintf(stats, "    Created: %s\n   Restaurant time: %s\n    Driver time: %s\n   Client time (end): %s\n     Total time: %s\n \n",
                   timespec_to_date(results[i].start_time),
                   timespec_to_date(results[i].rest_time),
                   timespec_to_date(results[i].driver_time),
                   timespec_to_date(results[i].client_end_time),
                   timespec_to_seconds(total_time));
        
    }
}