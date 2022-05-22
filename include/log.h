//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <metime.h>
#include <sys/time.h>
#include <mesignal.h>

//Função que regista uma operação no fihceiro log.txt
void regista_log(char* nome, char* instruction, int arg, struct timespec time);