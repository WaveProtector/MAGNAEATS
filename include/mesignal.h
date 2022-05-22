//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include "memory.h"
#include "main.h"
#include "configuration.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//Cria variaveis globais em mesignal.c para poder serem passadas para o handler ctrl + C no stop_execution
void get_params(struct main_data *data, struct semaphores *sems);

//Imprime no terminal os dados de cada request feito
void sig_handler();

//Cria um alarme que dispara a cada config.alarm_time segundos.
void create_alarm(struct main_data* data, struct config *config);

//Handler do ctrl + C
void ctrlC (int sig);

//Captura do sinal ctrl + C e chama o seu handler
void signal_ctrlC(struct main_data* data, struct semaphores* sems);
