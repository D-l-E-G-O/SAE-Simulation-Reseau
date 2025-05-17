#pragma once
#include <adresse.h>
typedef enum {
    RACINE = 0,
    DESIGNE = 1,
    NONDESIGNE = 2
} Port;

typedef struct com
{
    mac addr_mac;
    Port port;
}com;



