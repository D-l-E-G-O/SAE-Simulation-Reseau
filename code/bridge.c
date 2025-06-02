#include "bridge.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init_bridge(bridge* bd, size_t nb_ports, size_t priorite) {
    bd->nb_ports = nb_ports;
    bd->priorite = priorite;

    bd->table = (com*)malloc(sizeof(com) * nb_ports);
    bd->table_length = 0;
    bd->max_table_length = nb_ports;

    bd->ports = (port**)malloc(sizeof(port*) * nb_ports);
    memset(bd->ports,0, sizeof(port*)*nb_ports);
}


void desinit_bridge(bridge* bd) {
    if (!bd) return;

    for (size_t i = 0; i < bd->nb_ports; i++) {
        if (bd->ports[i]) {
            desinit_inter(bd->ports[i]->port);
            bd->ports[i]->type = 0;
            free(bd->ports[i]->port);
            free(bd->ports[i]);
            bd->ports[i] = NULL;
        }
    }

    free(bd->ports);
    bd->ports = NULL;

    free(bd->table);
    bd->table = NULL;

    bd->table_length = 0;
    bd->max_table_length = 0;
    bd->nb_ports = 0;
}

int check_if_in_com_table(bridge* bd, mac addr) {
    if (!bd || !bd->table) return -1;

    for (int i = 0; i < bd->table_length; i++) {
        if (memcmp(&bd->table[i].addr_mac, &addr, sizeof(mac)) == 0) {
            return i;
        }
    }
    return -1;
}

void add_to_com_table(bridge* bd, mac addr, interface* inter) {
    if (!bd || !inter) return;
    if (check_if_in_com_table(bd, addr) != -1) return;

    if (bd->table_length == bd->max_table_length) {
        size_t new_size = bd->max_table_length * 2;
        com* new_table = (com*)realloc(bd->table, sizeof(com) * new_size);
        if (!new_table) return;

        bd->table = new_table;
        bd->max_table_length = new_size;
    }

    size_t interface_index = (size_t)-1;
    for (size_t i = 0; i < bd->nb_ports; i++) {
        if (bd->ports[i]->port == inter) {
            interface_index = i;
            break;
        }
    }

    if (interface_index == (size_t)-1) return;

    memcpy(&bd->table[bd->table_length].addr_mac, &addr, sizeof(mac));
    bd->table[bd->table_length].index_port = interface_index;
    bd->table_length++;
}

interface* bridge_get_free_interface(bridge* bd, machine* mach) {
    if (!bd) return NULL;

    for (size_t i = 0; i < bd->nb_ports; i++) {
        if (bd->ports[i] == NULL) {
            interface* new_inter = malloc(sizeof(interface));
            if (!new_inter) return NULL;

            printf("je vais bind la nouvelle interface\n");
            init_interface(new_inter, mach);
            
            bd->ports[i] = malloc(sizeof(port));
            if (!bd->ports[i]) {
                free(new_inter);
                return NULL;
            }

            bd->ports[i]->port = new_inter;
            bd->ports[i]->type = DESIGNE; 
            return new_inter;
        }
    }

    return NULL; 
}


void print_switch_table(const bridge* bd) {
    if (!bd || !bd->table) {
        printf("Table de commutation vide ou bridge invalide.\n");
        return;
    }

    printf("┌───────────────────────────────────────────┐\n");
    printf("│       Table de commutation du bridge      │\n");
    printf("├─────────────────────┬─────────────────────┤\n");
    printf("│     Adresse MAC     │   Port d'interface  │\n");
    printf("├─────────────────────┼─────────────────────┤\n");

    if (bd->table_length == 0) {
        printf("│         Vide        │          -          │\n");
    } else {
        for (size_t i = 0; i < bd->table_length; i++) {
            printf("│  %s  ",to_string_mac(&bd->table[i].addr_mac, (char[20]){0}));
            printf("│ %10zu          │\n", bd->table[i].index_port);
        }
    }

    printf("└─────────────────────┴─────────────────────┘\n");
    printf("Total entrées: %zu / %zu\n", bd->table_length, bd->max_table_length);
}