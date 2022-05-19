#include "memory.h"
#include "main.h"
#include "configuration.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void create_alarm(struct operation* op, struct config* config);

void ctrlC (int sig, struct main_data* data, struct semaphores* sems);

void signal_ctrlC(struct main_data* data, struct semaphores* sems);
