#include <bridge.h>
#include <stdlib.h>

void init_bridge(bridge* bd,mac macaddr,size_t nb_ports,size_t priorite){
    bd->addr_eth = macaddr;
    bd->nb_ports = nb_ports;
    bd->priorite = priorite;
    bd->table = (com*)malloc(sizeof(com)*nb_ports);
    
};

void add_interface_bridge(bridge * bd,interface* inter){
    bd->interface = inter;
};

void desinit_bridge(bridge* bd){
    bd->addr_eth = 0;
    free(bd->table);
    free(bd->interface);
    bd->table = NULL;
}