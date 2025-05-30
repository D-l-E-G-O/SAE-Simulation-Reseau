#include <machine.h>
#include <stdlib.h>
#include <stdio.h>
void init_machine(machine* machine, void* machine_pointer, type type, mac addr) {
    machine->machine = machine_pointer;
    machine->type = type;
    machine->add_mac = addr;
    if (type == SWITCH) {
        char macprintbuffer[1024]; 
        bridge *br = (bridge *)(machine->machine); 
        printf("Switch: MAC=%s, Ports=%ld, Priorite=%ld\n",
               to_string_mac(&addr, macprintbuffer),
               br->nb_ports,
               br->priorite);
        machine->interface = NULL;
    } else {
        char bufferIP[1024];
        station *sta = (station *)(machine->machine); 
        printf("Station: MAC=%s, IP=%s\n", 
               to_string_mac(&addr, bufferIP), 
               to_string_ipv4(&sta->addr_ip, bufferIP));
        machine->interface = malloc(sizeof(interface));
        if (!machine->interface) {
            fprintf(stderr, "Erreur d'allocation interface station\n");
            exit(EXIT_FAILURE);
        }
        init_interface(machine->interface, machine);
    }
}

void desinit_machine(machine* machine) {
    char macprintbuffer[1024]; 
    printf(" desinit de : %s\n", to_string_mac(&machine->add_mac, macprintbuffer));
    
    if(machine->type == SWITCH) {
        desinit_bridge((bridge*)machine->machine);
    } else {
        desinit_station((station*)machine->machine);
    }
    
    machine->add_mac = -1;
    
    // Désallocation spécifique aux stations
    if (machine->type == STATION && machine->interface) {
        desinit_inter(machine->interface);
        free(machine->interface);
        machine->interface = NULL;
    }
    
    free(machine->machine);
}



void send_trame(machine* sender,trame *tr){
    send_data(sender->interface,tr);
};

void receive_tram(machine* receiver,trame*tr, machine* sender){

};


void connect_two_machine(machine* machine1, machine* machine2) {
    interface *intf1 = NULL, *intf2 = NULL;

    if (machine1->type == SWITCH) {
        bridge* br = (bridge*)machine1->machine;
        intf1 = bridge_get_free_interface(br, machine1);
    } else {
        intf1 = machine1->interface;
    }

    if (machine2->type == SWITCH) {
        bridge* br = (bridge*)machine2->machine;
        intf2 = bridge_get_free_interface(br, machine2);
    } else {
        intf2 = machine2->interface;
    }

    if (intf1 && intf2) {
        printf("Connexion entre %ld et %ld\n", 
               intf1->machine->add_mac, 
               intf2->machine->add_mac);
        connect_two_interface(intf1, intf2);
    } else {
        fprintf(stderr, "Erreur: interface non disponible\n");
    }
}