#pragma once
#include <adress.h>
#include <stddef.h>

typedef struct root_id {
    int8_t priorite;
    mac addr_mac;
}root_id;

typedef struct bpdu {
    root_id root;
    size_t cost;
    mac transmitting_id;
}bpdu;

bool is_root_id_inferior_to(root_id r1, root_id r2);

bool root_id_equals(root_id r1, root_id r2);

bpdu get_best_bpdu(bpdu machine1, bpdu machine2);