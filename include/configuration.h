//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <stdio.h>
#include <stdlib.h>

#include <main.h>

struct config {

    char* log_name; //nome do ficheiro de log
    char* stat_name; //nome do ficheiro de estatística

    int alarm_time; //tempo de alarme
};

/* Função que lê os parâmetros do ficheiro config.txt, nomeadamente o número
* máximo de operações, o tamanho dos buffers de memória partilhada
* usados para comunicação, e o número de clientes, de motoristas e de
* restaurantes. Guarda esta informação nos campos apropriados da
* estrutura main_data.
*
* Lê também o o nome do ficheiro de log, o nome do ficheiro de estatística e 
* o tempo de alarme. Guarda esta informação na estrutura de dados config.
*/
void get_config_params(struct main_data *data, struct config config, char *argv[]);

