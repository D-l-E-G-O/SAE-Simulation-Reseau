#pragma once
#include <adress.h>
#include <stddef.h>

typedef struct root_id {
    int16_t priorite;
    mac addr_mac;
}root_id;

typedef struct bpdu {
    root_id root;
    size_t cost;
    mac transmitting_id;
}bpdu;

void init_root_id(root_id* root_id, int16_t priorite, mac addr_mac);

void init_bpdu(bpdu* bpdu, int16_t priorite, mac addr_mac);

void set_cost(bpdu* bpdu, size_t cost);

bool is_root_id_inferior_to(root_id r1, root_id r2);

bool root_id_equals(root_id r1, root_id r2);

bpdu* get_best_bpdu(bpdu* machine1, bpdu*  machine2);

char* to_string_bpdu(bpdu bpdu, char* buffer);

size_t to_int_string_bpdu(char* string_bpdu);

char* to_string_int_bpdu(size_t int_bpdu, char* buffer);