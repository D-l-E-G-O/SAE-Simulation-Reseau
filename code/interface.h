#pragma once
#include <trame.h>

typedef struct interface
{
    machine* machine;//pointeur vers la machinne qui à l'interface
    struct interface* connected_to;//interface à qui cette interface est connecté
    
}interface;



void init_interface(interface * inter,void* machine);

void connect_two_interface(interface* a, interface* b);

void send_data(interface* sender,trame * data);

void receive_data(interface *receiver,trame * data);
