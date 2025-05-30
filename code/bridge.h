#pragma once

#include <stddef.h>
#include <port.h>
#include <interface.h>
#include <adress.h>
#include <machine.h>

typedef struct interface interface;
typedef struct machine machine;

typedef struct bridge {
    size_t nb_ports;
    size_t priorite;
    size_t table_length;
    size_t max_table_length;
    com* table;
    interface** ports;
} bridge;

void init_bridge(bridge* bd, size_t nb_ports, size_t priorite);
void desinit_bridge(bridge* bd);
void add_to_com_table(bridge* bd, mac addr, interface* inter);
int check_if_in_com_table(bridge* bd, mac addr);
interface* bridge_get_free_interface(bridge* bd,machine* mach);

void print_switch_table(const bridge* bd);