#pragma once
#include <trame.h>
#include <machine.h>

typedef struct machine machine;


typedef struct interface
{
    machine* machine; //Pointeur vers la machinne qui a l'interface
    struct interface* connected_to; //Interface à qui cette interface est connectée
    
}interface;



void init_interface(interface * inter,machine* machine);
void desinit_inter(interface* inter);

void connect_two_interface(interface* a, interface* b);

void send_data(interface* sender,trame * data);

void receive_data(interface *receiver,trame * data);
