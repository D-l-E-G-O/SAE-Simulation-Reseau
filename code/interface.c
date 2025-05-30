#include <interface.h>


void init_interface(interface * inter,void* machine,type type){
    inter->machine = machine;
    inter->type = type;
};

void connect_two_interface(interface* a, interface* b){//c'est comme si on connecter les deux interfaces avec un câble
    a->connected_to = b;
    b->connected_to = a;
};

void send_data(interface* sender,trame * data){//envoie les data via le "cable" qui est connecter à l'interface
    receive_data(sender->connected_to,data);
};

void receive_data(interface *receiver,trame * data){
}