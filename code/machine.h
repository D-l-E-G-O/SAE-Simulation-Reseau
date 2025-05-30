#pragma once

#include <bridge.h>
#include <station.h>

typedef enum{
    STATION = 1,
    SWITCH = 2,
}type;

typedef struct machine{
    void* machine;
    type type;
}machine;

void init_machine(machine*  machine,void* machine_pointer,type type);

void desinit_machine(machine machine);

void connect_two_machine(machine* machine1,machine* machine2);
