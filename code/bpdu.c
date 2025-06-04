#include <bpdu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void init_root_id(root_id* root_id, int16_t priorite, mac addr_mac){
    root_id->priorite = priorite;
    root_id->addr_mac = addr_mac;
}

void init_bpdu(bpdu* bpdu, int16_t priorite, mac addr_mac){
    bpdu->root = (root_id*) malloc(sizeof(root_id));
    init_root_id(bpdu->root, priorite, addr_mac);
    bpdu->cost = 0;
    bpdu->transmitting_id = addr_mac;
}

void desinit_bpdu(bpdu * bpdu){
    free(bpdu->root);
    bpdu->root = NULL;
}

void set_cost(bpdu* bpdu, size_t cost){
    bpdu->cost = cost;
}

void copy_bpdu(bpdu* source, bpdu* dest) {
    init_bpdu(dest, source->root->priorite, source->root->addr_mac);
    set_cost(dest, source->cost);
    dest->transmitting_id = source->transmitting_id; 
}

bool is_root_id_inferior_to(root_id* r1, root_id* r2){
    if (r1->priorite < r2->priorite || (r1->priorite == r2->priorite && is_mac_inferior_to(r1->addr_mac, r2->addr_mac))){
        return true;
    }
    else{
        return false;
    }
}

bool root_id_equals(root_id* r1, root_id* r2){
    return (r1->priorite == r2->priorite && mac_equals(r1->addr_mac, r2->addr_mac));
}

bool is_bpdu_better(bpdu* received, bpdu* current) {
    if (!root_id_equals(received->root, current->root)) {
        return is_root_id_inferior_to(received->root, current->root);
    }
    if (received->cost != current->cost) {
        return received->cost < current->cost;
    }
    return is_mac_inferior_to(received->transmitting_id, current->transmitting_id);
}

void set_transmit(bpdu* tochange,mac addr){
    tochange->transmitting_id = addr;
}

char* to_string_bpdu(bpdu* bpdu, char* buffer) {
    if (!buffer || !bpdu || !bpdu->root) return NULL;
    
    char mac_root[20];
    char mac_transmitter[20];
    
    sprintf(buffer, "[%s,%zu,%s]", 
           to_string_mac(&bpdu->root->addr_mac, mac_root),
           bpdu->cost,
           to_string_mac(&bpdu->transmitting_id, mac_transmitter));
    
    return buffer;
}

size_t to_int_string_bpdu(char* string_bpdu){
    size_t n = strlen(string_bpdu);
    if (n == 0) return 0;
    size_t int_bpdu = string_bpdu[0];
    for(size_t i=1; i<n; i++){
        int_bpdu = (int_bpdu<<8 )+ string_bpdu[i];
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