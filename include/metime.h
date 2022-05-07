#include "memory.h"
#include "main.h"
#include "time.h"

//Estrutura que representa uma operação (pedido/resposta)
struct operation {
	int id; 					//id da operação
	int requested_rest;			//id do restaurante requisitado
	int requesting_client;		//id do cliente que fez o pedido
	char* requested_dish;		//nome do(s) prato(s) pedido(s)
	
	char status;				//estado da operação
	int receiving_rest;			//id do restaurante que recebeu pedido
	int receiving_driver;		//id do motorista que fez entrega
	int receiving_client;		//id do cliente que recebeu a encomenda

    struct timespec start_time;         //quando o pedido foi criado
    struct timespec rest_time;          //quando o restaurante recebeu
                                        //o pedido
    struct timespec driver_time;        //quando o motorista recebeu
                                        //o pedido
    struct timespec client_end_time;    //quando o cliente recebeu
                                        //e finalizou o pedido
};