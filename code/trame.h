#pragma once 
#include <adress.h>

typedef struct trame{
    mac source;
    mac dest;
    int message;
}trame;

void init_trame(trame * tra,mac source,mac dest);

