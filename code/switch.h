#pragma once
#include <port.h>

typedef struct Switch{
    mac addr_eth;
    size_t nb_ports;
    size_t priorite;
    com* table;
}

