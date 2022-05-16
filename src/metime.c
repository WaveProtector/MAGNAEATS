#include "metime.h"
#include "stdio.h";
#include "string.h";

void register_start_time(struct operation op) {
    clock_gettime(CLOCK_REALTIME, &op.start_time);
}

void register_rest_time(struct operation op) {
    clock_gettime(CLOCK_REALTIME, &op.rest_time);
}

void register_driver_time(struct operation op) {
    clock_gettime(CLOCK_REALTIME, &op.driver_time);
}

void register_driver_time(struct operation op) {
    clock_gettime(CLOCK_REALTIME, &op.client_end_time);
}

char* timespec_to_date(struct timespec time) {
    static char output[255]; //sem o static dá erro de compilação
    char ms[10]; //milisegundos
    sprintf(ms, "%3.0f", (time.tv_nsec / 1.0e6)); //convertemos os nanosegundos para milisegundos
    struct tm *current_tm = localtime(time.tv_sec); //passamos de timespec para tm usando os segundos do timespec para conseguirmos usar o strftime
    strftime(output, 30, "%Y-%m-%d %H:%M:%S.", current_tm); //formatamos a data para o tipo que queremos
    strcat(output, ms); //concatenamos a string da data para os milisegundos aparecerem no final
    return output;
}

char* timespec_to_seconds(struct timespec time) {
    static char output[255];
    char ms[10];
    sprintf(ms, "%3.0f", (time.tv_nsec / 1.0e6));
    struct tm *current_tm = localtime(time.tv_sec);
    strftime(output, 30, "%S.", current_tm);
    strcat(output, ms);
    return output;
}