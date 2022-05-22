//Projeto - 2ª fase realizado pelo grupo 21:
//João Assis, fc56325
//José Brás, fc55449
//Ricardo Mateus, fc56366

#include <metime.h>
#include <stdio.h>
#include <string.h>

void register_start_time(struct operation *op) {
    clock_gettime(CLOCK_REALTIME, &op->start_time);
}

void register_rest_time(struct operation *op) {
    clock_gettime(CLOCK_REALTIME, &op->rest_time);
}

void register_driver_time(struct operation *op) {
    clock_gettime(CLOCK_REALTIME, &op->driver_time);
}

void register_client_end_time(struct operation *op) {
    clock_gettime(CLOCK_REALTIME, &op->client_end_time);
}

char* timespec_to_date(struct timespec time) {
    static char output[255];
    char ms[10];
    sprintf(ms, "%3.0f", (time.tv_nsec / 1.0e6));
    struct tm *current_tm = localtime(&time.tv_sec);
    strftime(output, 30, "%Y-%m-%d %H:%M:%S.", current_tm);
    strcat(output, ms);
    return output;
}

char* timespec_to_seconds(struct timespec time) {
    static char output[255];
    char ms[10];
    sprintf(ms, "%3.0f", (time.tv_nsec / 1.0e6));
    struct tm *current_tm = localtime(&time.tv_sec);
    strftime(output, 30, "%S.", current_tm);
    strcat(output, ms);
    return output;
}