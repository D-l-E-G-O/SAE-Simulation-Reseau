#pragma once
#include <stddef.h>
#include <port.h>
#include <interface.h>

typedef struct bridge{
    mac addr_eth;
    size_t nb_ports;
    size_t priorite;
    com* table;
    interface* interface;

}bridge;


void init_bridge(bridge* bd,mac macaddr,size_t nb_ports,size_t priorite);

void desinit_bridge(bridge* bd);
void add_interface_bridge(bridge * bd,interface* inter);