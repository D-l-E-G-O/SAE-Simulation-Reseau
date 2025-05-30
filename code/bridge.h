#pragma once
#include <stddef.h>
#include <port.h>

typedef struct bridge{
    size_t nb_ports;
    size_t priorite;
    com* table;

}bridge;


void init_bridge(bridge* bd,size_t nb_ports,size_t priorite);

void desinit_bridge(bridge* bd);