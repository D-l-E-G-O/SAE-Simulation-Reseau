#include <bpdu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void init_root_id(root_id* root_id, size_t priorite, mac addr_mac){
    root_id->priorite = priorite;
    root_id->addr_mac = addr_mac;
}

void init_bpdu(bpdu* bpdu, size_t priorite, mac addr_mac){
    bpdu->root = (root_id*) malloc(sizeof(root_id));
    init_root_id(bpdu->root, priorite, addr_mac);
    bpdu->cost = 0;
    bpdu->transmitting_id = addr_mac;
}

void desinit_bpdu(bpdu * bpdu){
    free(bpdu->root);
    bpdu->transmitting_id =0;
    bpdu->root = NULL;
}

void set_cost(bpdu* bpdu, size_t cost){
    bpdu->cost = cost;
}

void copy_bpdu(bpdu* src, bpdu* dest) {
    dest->root = malloc(sizeof(root_id));
    memcpy(dest->root, src->root, sizeof(root_id));
    dest->cost = src->cost;
    memcpy(&dest->transmitting_id, &src->transmitting_id, sizeof(mac));
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
    if (!received || !current || !received->root || !current->root) return false;
    if (received->root->priorite < current->root->priorite) return true;
    if (received->root->priorite > current->root->priorite) return false;
    if (is_mac_inferior_to(received->root->addr_mac, current->root->addr_mac)) return true;
    if (is_mac_inferior_to(current->root->addr_mac, received->root->addr_mac)) return false;
    if (received->cost < current->cost) return true;
    if (received->cost > current->cost) return false;
    return is_mac_inferior_to(received->transmitting_id, current->transmitting_id);
}

void set_transmit(bpdu* tochange,mac addr){
    tochange->transmitting_id = addr;
}

char* to_string_bpdu(bpdu* bpdu, char* buffer) {
    if (!buffer || !bpdu || !bpdu->root) return NULL;
    
    char mac_root[20];
    char mac_transmitter[20];
    
    sprintf(buffer, "[%d + %s   ,  %zu   ,%s]", 
            bpdu->root->priorite,
           to_string_mac(&bpdu->root->addr_mac, mac_root),
           bpdu->cost,
           to_string_mac(&bpdu->transmitting_id, mac_transmitter));
    
    return buffer;
}



void afficher_bpdu(bpdu* b) {
    if (!b || !b->root) {
        printf("BPDU invalide.\n");
        return;
    }

    char buffer[100];  
    if (to_string_bpdu(b, buffer)) {
        printf("BPDU: %s\n", buffer);
    } else {
        printf("Erreur lors de la conversion du BPDU en chaîne.\n");
    }
}
