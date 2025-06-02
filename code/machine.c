#include <machine.h>
#include <stdlib.h>
#include <stdio.h>

void init_machine(machine* machine, void* machine_pointer, type type, mac addr) {
    machine->machine = machine_pointer;
    machine->type = type;
    machine->addr_mac = addr;
    if (type == SWITCH) {
        char macprintbuffer[1024]; 
        bridge *br = (bridge *)(machine->machine); 
        printf("Switch: MAC=%s, Ports=%ld, Priorite=%ld\n",
               to_string_mac(&addr, macprintbuffer),
               br->nb_ports,
               br->priorite);
        machine->interface = malloc(sizeof(interface));
        
    } else {
        char bufferIP[1024];
        station *sta = (station *)(machine->machine); 
        printf("Station: MAC=%s, IP=%s\n", 
               to_string_mac(&addr, bufferIP), 
               to_string_ipv4(&sta->addr_ip, bufferIP));
        machine->interface = malloc(sizeof(interface));
        if (!machine->interface) {
            exit(EXIT_FAILURE);
        }
        
    }
    init_interface(machine->interface, machine);
}

void desinit_machine(machine* machine) {
    char macprintbuffer[1024]; 
    printf(" desinit de : %s\n", to_string_mac(&machine->addr_mac, macprintbuffer));
    
    if(machine->type == SWITCH) {
        desinit_bridge((bridge*)machine->machine);
    } else {
        desinit_station((station*)machine->machine);
    }
    
    machine->addr_mac = -1;
    
    desinit_inter(machine->interface);
    free(machine->interface);
    machine->interface = NULL;

    
    free(machine->machine);
}

void send_trame(machine* sender, trame *tr, interface* input_port) {
    if (sender->type == STATION) {
        send_data(sender->interface, tr);
    } else if (sender->type == SWITCH) {
        bridge *br = (bridge*)sender->machine;
        int index = check_if_in_com_table(br, tr->dest);
        
        if (index != -1) {
            com* entry = &br->table[index];
            interface* out_inter = br->ports[entry->index_port]->port;
            send_data(out_inter, tr);
        } else {
            for (size_t i = 0; i < br->nb_ports; i++) {
                if (br->ports[i] && (br->ports[i]->port != input_port)) {
                    send_data(br->ports[i]->port, tr);
                }
            }
        }
    }
}

bool is_it_for_me_question_mark(machine *mach,trame* t){
    return(compare_mac(&mach->addr_mac,&t->dest));
}

void receive_tram(machine* receiver, trame* tr, interface* input_port) {
    char mac_buffer[20];
    if (receiver->type == STATION) {
        if (is_it_for_me_question_mark(receiver, tr)) {
            printf("Station %s: reçu trame de %s: [dest=%s, message=%d]\n",
                   to_string_mac(&receiver->addr_mac, mac_buffer),
                   to_string_mac(&tr->source, mac_buffer),
                   to_string_mac(&tr->dest, mac_buffer),
                   tr->message);

            if (tr->message == 0) {
                trame reply;
                init_trame(&reply, receiver->addr_mac, tr->source, 1);
                send_trame(receiver, &reply, receiver->interface);
            }
        }
    } else if (receiver->type == SWITCH) {
        bridge *br = (bridge*)receiver->machine;
        printf("Switch %s: reçu trame de %s vers %s\n",
               to_string_mac(&receiver->addr_mac, mac_buffer),
               to_string_mac(&tr->source, mac_buffer),
               to_string_mac(&tr->dest, mac_buffer));

        if (input_port) {
            add_to_com_table(br, tr->source, input_port);
        } else {
            printf(" Avertissement: port d'entrée inconnu\n");
        }

        send_trame(receiver, tr, input_port);
    }
}

void connect_two_machine(machine* machine1, machine* machine2, size_t poids) {
    interface *intf1 = NULL, *intf2 = NULL;
    assign_interface(&machine1, &intf1);
    assign_interface(&machine2, &intf2);

    if (intf1 && intf2) {
        connect_two_interface(intf1, intf2, poids);
    } else {
        fprintf(stderr, "Erreur: interface non disponible\n");
    }
}

void assign_interface(machine** machine, interface** interface){
    if ((*machine)->type == SWITCH) {
        bridge* br = (bridge*)(*machine)->machine;
        *interface = bridge_get_free_interface(br, *machine);
    } else {
        *interface = (*machine)->interface;
    }
}
