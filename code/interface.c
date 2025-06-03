#include <interface.h>
#include <stdio.h>
#include <stdlib.h>

void init_interface(interface* inter, machine* machine) {
    if (!inter) return;
    inter->machine = machine;
    inter->connected_to = NULL;
    inter->poids = -1;
};

void desinit_inter(interface* inter){
    inter->machine = NULL;
}

void connect_two_interface(interface* a, interface* b, size_t poids){ //C'est comme si on connectait les deux interfaces avec un câble
    a->connected_to = b;
    a->poids = poids;
    b->connected_to = a;
    b->poids = poids;
    printf("Connexion: %s <-> %s (Poids: %zu)\n",
       to_string_mac(&a->machine->addr_mac,  (char[20]){0}),
       to_string_mac(&b->machine->addr_mac,  (char[20]){0}),
       poids
    );
};

void send_data(interface *intf, void *tr) { //Ca envoie les données dans le "câble"
    if (intf->connected_to && intf->connected_to->machine) {
        receive_tram(intf->connected_to->machine, tr, intf->connected_to);
    }
}

void receive_data(interface *receiver, void *data) {
    if (receiver->machine) {
        receive_tram(receiver->machine, data, receiver);
    }
}