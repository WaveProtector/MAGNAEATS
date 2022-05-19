#include "metime.h"
#include <sys/time.h>

char* le_nome_ficheiro ();

void regista_log (char* file_name, char* instruction, struct timespec time);