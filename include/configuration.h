#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct config {
    char* log_name;
    char* stat_name;

    int alarm_time;
};

/* Função que lê os argumentos da aplicação, nomeadamente o número
* máximo de operações, o tamanho dos buffers de memória partilhada
* usados para comunicação, e o número de clientes, de motoristas e de
* restaurantes. Guarda esta informação nos campos apropriados da
* estrutura main_data.
*/
void get_config_params(struct main_data *data);

