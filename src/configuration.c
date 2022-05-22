//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <configuration.h>
#define MAXLINHA 64

void get_config_params(struct main_data* data, struct config *config)
{
    FILE *conf = fopen("config.txt", "r");
    char line[10][MAXLINHA];
    int i;
    for (i = 0; i < 8; i++)
    {
        fgets(line[i], MAXLINHA, conf);
    }
    data->max_ops = atoi(line[0]);
    data->buffers_size = atoi(line[1]);
    data->n_restaurants = atoi(line[2]);
    data->n_drivers = atoi(line[3]);
    data->n_clients = atoi(line[4]);
    config->log_name = line[5];
    config->stat_name = line[6];
    config->alarm_time = atoi(line[7]);
    fclose(conf);
}