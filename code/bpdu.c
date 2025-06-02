#include <bpdu.h>


void init_root_id(root_id* root_id, int8_t priorite, mac addr_mac){
    root_id->priorite = priorite;
    root_id->addr_mac = addr_mac;
}

void init_bpdu(bpdu* bpdu, root_id root, size_t cost, mac transmitting_id){
    bpdu->root = root;
    bpdu->cost = cost;
    bpdu->transmitting_id = transmitting_id;
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

bpdu get_best_bpdu(bpdu machine1, bpdu machine2){
    if (is_root_id_inferior_to(machine1.root, machine2.root)
        || (root_id_equals(machine1.root, machine2.root) && machine1.cost < machine2.cost)
        || (root_id_equals(machine1.root, machine2.root) && machine1.cost == machine2.cost && is_mac_inferior_to(machine1.transmitting_id, machine2.transmitting_id))){
        return machine1;
    }
    else {
        return machine2;
    }
}