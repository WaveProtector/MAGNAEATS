#include "metime.h"

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
    time(op.client_end_time);
}