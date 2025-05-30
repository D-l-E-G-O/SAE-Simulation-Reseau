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
    printf("Connexion entre %s et %s\n", to_string_mac(&a->machine->add_mac, (char[20]){0}),to_string_mac(&b->machine->add_mac, (char[20]){0}));
};

void send_data(interface* sender,trame * data){//envoie les data via le "cable" qui est connecter à l'interface
    receive_data(sender->connected_to,data);
};

void receive_data(interface *receiver,trame * data){
    receive_tram(receiver->machine,data,receiver->machine);
}