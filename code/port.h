#pragma once
#include "adress.h"
typedef enum {
    RACINE = 0,
    DESIGNE = 1,
    NONDESIGNE = 2
} port;

typedef struct com
{
    mac addr_mac;
    port port;
}com;



