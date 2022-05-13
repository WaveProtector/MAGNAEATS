#include "metime.h"

//estrutura que compõe os campos no ficheiro de estatísticas
struct stats {
    int* restaurant_ids;          //id do restaurante que preparou as requests
    int* driver_ids;              //id do driver que entregou as requests
    int* client_ids;              //id do client que recebeu as requests

    int* request_ids;             //Número da request
    //TODO maybe

};

//TODO