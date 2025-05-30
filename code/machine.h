#pragma once

#include <bridge.h>
#include <station.h>
#include <interface.h>
typedef struct interface interface;
typedef enum{
    STATION = 1,
    SWITCH = 2,
}type;


typedef struct machine{
    void* machine;
    interface * interface;
    type type;
    mac add_mac;
}machine;

void init_machine(machine*  machine,void* machine_pointer,type type,mac addr);

void desinit_machine(machine* machine);

void connect_two_machine(machine* machine1,machine* machine2);

void add_interface(machine* machine , interface * inter);

void send_trame();

