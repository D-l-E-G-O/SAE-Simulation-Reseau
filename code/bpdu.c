#include <bpdu.h>


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