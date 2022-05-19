//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <metime.h>
#include <string.h>
#include <stdio.h>

char* le_nome_ficheiro () {
    FILE *config = fopen("../config.txt", "r");
    char line[100];
    char file_src[50] = "../";
    char* file_name;
    int count = 0; 
    int lineNumber = 5;
    char foundLine = 0;

    while (foundLine == 0) {  
        fgets(line, sizeof line, config);
        if (count == lineNumber) {
            file_name = strcat(file_src, line); 
            foundLine++;
        } else {
            count++;
        }
    }

    fclose(config);
    return file_name;
}

void regista_log (char* file_name, char* instruction, struct timespec time) {
   
    FILE *f;
    f = fopen(file_name, "w");
    fprintf(f, "%s %s \n", timespec_to_date(time), instruction);
    fclose(f);

}
