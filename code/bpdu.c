#include <bpdu.h>
#include <stdio.h>
#include <string.h>


void init_root_id(root_id* root_id, int16_t priorite, mac addr_mac){
    root_id->priorite = priorite;
    root_id->addr_mac = addr_mac;
}

void init_bpdu(bpdu* bpdu, int16_t priorite, mac addr_mac){
    init_root_id(&bpdu->root, priorite, addr_mac);
    bpdu->cost = 0;
    bpdu->transmitting_id = addr_mac;
}

void set_cost(bpdu* bpdu, size_t cost){
    bpdu->cost = cost;
}

bool is_root_id_inferior_to(root_id r1, root_id r2){
    if (r1.priorite < r2.priorite || (r1.priorite == r2.priorite && is_mac_inferior_to(r1.addr_mac, r2.addr_mac))){
        return true;
    }
    else{
        return false;
    }
}

bool root_id_equals(root_id r1, root_id r2){
    return (r1.priorite == r2.priorite && mac_equals(r1.addr_mac, r2.addr_mac));
}

bpdu* get_best_bpdu(bpdu* machine1, bpdu* machine2){
    if (is_root_id_inferior_to(machine1->root, machine2->root)
        || (root_id_equals(machine1->root, machine2->root) && machine1->cost < machine2->cost)
        || (root_id_equals(machine1->root, machine2->root) && machine1->cost == machine2->cost && is_mac_inferior_to(machine1->transmitting_id, machine2->transmitting_id))){
        return machine1;
    }
    else {
        return machine2;
    }
}

char* to_string_bpdu(bpdu bpdu, char* buffer){
    if (!buffer) return NULL;
    char buffer_root[64];
    char buffer_transmitter[64];
    sprintf(buffer, "[%s,%zu,%s]", to_string_mac(&bpdu.root.addr_mac, buffer_root), bpdu.cost, to_string_mac(&bpdu.transmitting_id, buffer_transmitter));
    return buffer;
}

size_t to_int_string_bpdu(char* string_bpdu){
    size_t n = strlen(string_bpdu);
    if (n == 0) return 0;
    size_t int_bpdu = string_bpdu[0];
    for(size_t i=1; i<n; i++){
        int_bpdu = int_bpdu<<8 + string_bpdu[i];
    }
    return int_bpdu;
}

char* to_string_int_bpdu(size_t int_bpdu, char* buffer){
    size_t nb_octets = 0;
    while(int_bpdu >> 8*nb_octets != 0){
        nb_octets++;
    }
    uint8_t masque = 15; //1 octet binaire remplit avec des 1;
    for(size_t i=nb_octets; i>0; i--){
        buffer[i] = int_bpdu & masque;
        masque <<= 8;
    }
    return buffer;
}