#include <interface.h>
#include <stdio.h>
#include <stdlib.h>

void init_interface(interface* inter, machine* machine) {
    if (!inter) return;
    
    inter->machine = machine;
    inter->connected_to = NULL; 
};

void desinit_inter(interface* inter){
    inter->machine = NULL;
}

void connect_two_interface(interface* a, interface* b){//c'est comme si on connecter les deux interfaces avec un câble
    a->connected_to = b;
    b->connected_to = a;
    printf("Connexion: %s <-> %s\n",
       to_string_mac(&a->machine->addr_mac,  (char[20]){0}),
       to_string_mac(&b->machine->addr_mac,  (char[20]){0}));
};

void send_data(interface *intf, trame *tr) {//ça envoie dans le "câble"
    if (intf->connected_to && intf->connected_to->machine) {
        receive_tram(intf->connected_to->machine, tr, intf->connected_to);
    }
}

void receive_data(interface *receiver, trame *data) {
    if (receiver->machine) {
        receive_tram(receiver->machine, data, receiver);
    }
}