#include "metime.h"
#include "stdio.h";
#include "string.h";

void register_start_time(struct operation op) {
    time(op.start_time);
}

void register_rest_time(struct operation op) {
    time(op.rest_time);
}

void register_driver_time(struct operation op) {
    time(op.driver_time);
}

void register_driver_time(struct operation op) {
    clock_gettime(CLOCK_REALTIME, &op.client_end_time);
}

char* timespec_to_date(struct timespec time) {
    char* output;
    char* ms; //milisegundos
    sprintf(ms, "%.3f", time.tv_nsec);
    struct tm *current_tm = localtime(time.tv_sec); //passamos os milisegundos para uma data normal
    strftime(output, 30, "%Y-%m-%d %H:%M:%S.", current_tm); //formatamos a data para o tipo que queremos
    strcat(output, ms); //concatenamos a string para os milisegundos aparecerem no final
    return output;
}

char* timespec_to_seconds(struct timespec time) {
    char* output;
    char* ms;
    sprintf(ms, "%.3f", time.tv_nsec);
    struct tm *current_tm = localtime(time.tv_sec);
    strftime(output, 30, "%S.", current_tm);
    strcat(output, ms);
    return output;
}