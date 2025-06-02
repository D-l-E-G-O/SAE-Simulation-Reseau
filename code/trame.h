#pragma once 
#include <adress.h>
#include <stddef.h>

typedef struct trame{
    mac source;
    mac dest;
    size_t message;
}trame;

void init_trame(trame * tra, mac source, mac dest, size_t message);

