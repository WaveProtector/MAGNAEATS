//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <metime.h>
#include <sys/time.h>

char* le_nome_ficheiro ();

void regista_log (char* file_name, char* instruction, struct timespec time);