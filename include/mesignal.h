#include "memory.h"
#include "main.h"
#include "configuration.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//Imprime no terminal os dados de cada request feito
void sig_handler();


//Cria um alarme que dispara a cada config.alarm_time segundos.
void create_alarm(struct main_data* data, struct config config);

void ctrlC (int sig, struct main_data* data, struct semaphores* sems);

void signal_ctrlC(struct main_data* data, struct semaphores* sems);
