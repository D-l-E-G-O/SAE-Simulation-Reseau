#include "bridge.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void init_bridge(bridge* bd, size_t nb_ports, size_t priorite, mac addr_mac) {
    bd->nb_ports = nb_ports;
    bd->priorite = priorite;
    bd->addr_mac = addr_mac;
    bd->bpdu = (bpdu*)malloc(sizeof(bpdu));
    if (!bd->bpdu) return;
    
    init_bpdu(bd->bpdu, priorite, addr_mac);
    printf("Switch: MAC=%s, Ports=%zu, Priorite=%zu\n", 
           to_string_mac(&addr_mac, (char[20]){0}), nb_ports, priorite);
    
    bd->table = (com*)malloc(sizeof(com) * nb_ports);
    bd->table_length = 0;
    bd->max_table_length = nb_ports;

    bd->ports = (port**)calloc(nb_ports, sizeof(port*));
    bd->root_index = -1;
}

void desinit_bridge(bridge* bd) {
    if (!bd) return;

    for (size_t i = 0; i < bd->nb_ports; i++) {
        if (bd->ports[i]) {
            desinit_inter(bd->ports[i]->port);
            bd->ports[i]->type = 0;
            bd->ports[i]->type_changed=false;
            free(bd->ports[i]->port);
            free(bd->ports[i]);
            bd->ports[i] = NULL;
        }
    }

    free(bd->ports);
    bd->ports = NULL;

    desinit_bpdu(bd->bpdu);
    free(bd->bpdu);
    bd->bpdu = NULL;



    free(bd->table);
    bd->table = NULL;

    bd->table_length = 0;
    bd->max_table_length = 0;
    bd->nb_ports = 0;
    bd->root_index=-1;
    

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

            init_interface(new_inter, mach);
            
            bd->ports[i] = malloc(sizeof(port));
            if (!bd->ports[i]) {
                free(new_inter);
                return NULL;
            }

            bd->ports[i]->port = new_inter;
            bd->ports[i]->type = DESIGNE; 
            bd->ports[i]->type_changed=false;
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



int retrieve_port(bridge* bd, interface* inter) {
    if (!bd || !inter) return -1;

    for (size_t i = 0; i < bd->nb_ports; i++) {
        if (bd->ports[i] && bd->ports[i]->port == inter) {
            return (int)i;
        }
    }

    return -1;
}





void process_trame(bridge *br, trame* tr, interface* input_port) {
    int input_index = retrieve_port(br, input_port);
    if (input_index == -1) {
        printf("Erreur : interface d'entrée non trouvée dans le bridge.\n");
        return;
    }

    if (tr->type == PING) {
        int index = check_if_in_com_table(br, tr->dest);
        if (index != -1) {
            com* entry = &br->table[index];
            interface* out_inter = br->ports[entry->index_port]->port;

            if (out_inter != input_port) {
                trame reply;
                copy_trame(&reply, tr);
                send_data(out_inter, &reply);
                desinit_trame(&reply); 
            }
        } else {
            for (size_t i = 0; i < br->nb_ports; i++) {
                if (br->ports[i] && (br->ports[i]->port != input_port&& br->ports[i]->type !=NONDESIGNE)) {
                    trame reply;
                    copy_trame(&reply, tr);
                    send_data(br->ports[i]->port, &reply);
                    desinit_trame(&reply); 
                }
            }
        }
    }

    if (tr->type == BPDU) {
        bpdu* bp = (bpdu*)tr->message;
        if (is_bpdu_better(br->bpdu,bp)) { 
            int old_root = br->root_index;
            br->root_index = input_index;
            br->ports[input_index]->type = RACINE;
            br->ports[input_index]->type_changed = true;
            if (old_root != -1 && old_root != input_index) {
                br->ports[old_root]->type = NONDESIGNE;
                br->ports[old_root]->type_changed = true;
            }
            desinit_bpdu(br->bpdu);  
            br->bpdu = (bpdu*)malloc(sizeof(bpdu));
            if (!br->bpdu) return; 
            copy_bpdu(bp, br->bpdu);
        }
        recalculate_ports(br, bp);
    }
}




void send_bdpu(bridge *br) {
    if (!br || !br->bpdu || !br->ports) return;

    for (size_t i = 0; i < br->nb_ports; i++) {
        if (br->ports[i] && br->ports[i]->type != NONDESIGNE && br->ports[i]->port) {
            trame tr;
            bpdu bp;
            copy_bpdu(br->bpdu, &bp);
            set_cost(&bp, bp.cost + br->ports[i]->port->poids);
            init_trame(&tr, br->addr_mac, br->addr_mac, &bp, BPDU);
            send_data(br->ports[i]->port, &tr);
            desinit_trame(&tr);
            desinit_bpdu(&bp);
        }
    }
}

void recalculate_ports(bridge* br, bpdu* received_bpdu) {
    if (!br || !received_bpdu) return;

    for (size_t i = 0; i < br->nb_ports; i++) {
        if (!br->ports[i] || !br->ports[i]->port) continue;

        interface* inter = br->ports[i]->port;

        if (inter->connected_to && inter->connected_to->machine->type != SWITCH) {
            if (br->ports[i]->type != DESIGNE) {
                br->ports[i]->type = DESIGNE;
                br->ports[i]->type_changed = true;
            }
            continue;
        }

        if ((int)i == br->root_index) continue;

        bpdu my_bpdu;
        copy_bpdu(br->bpdu, &my_bpdu);
        set_cost(&my_bpdu, my_bpdu.cost + inter->poids);

        bpdu* bp_received =received_bpdu;
        if (!bp_received) {
            desinit_bpdu(&my_bpdu);
            continue;
        }

        bool should_block = is_bpdu_better(bp_received, &my_bpdu);
        port_type new_type = should_block ? NONDESIGNE : DESIGNE;

        if (br->ports[i]->type != new_type) {
            br->ports[i]->type = new_type;
            br->ports[i]->type_changed = true;
        }

        desinit_bpdu(&my_bpdu);
    }
}
