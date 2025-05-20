#pragma once
#include <port.h>

typedef struct Bridge{
    mac addr_eth;
    size_t nb_ports;
    size_t priorite;
    com* table;
}

