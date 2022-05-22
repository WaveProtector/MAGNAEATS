//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <string.h>
#include <stdio.h>
#include <log.h>

void regista_log (char* nome, char* instruction, int arg, struct timespec time) {
    FILE *f;
    f = fopen(nome, "a");
    if (arg >= 1) 
        fprintf(f, "%s %s %d \n", timespec_to_date(time), instruction, arg);
    else 
        fprintf(f, "%s %s \n", timespec_to_date(time), instruction);
    fclose(f);
}
