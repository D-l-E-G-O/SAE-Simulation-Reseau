#include <bridge.h>
#include <stdlib.h>

void init_bridge(bridge* bd,size_t nb_ports,size_t priorite){
    bd->nb_ports = nb_ports;
    bd->priorite = priorite;
    bd->table = (com*)malloc(sizeof(com)*nb_ports);
    
};

void desinit_bridge(bridge* bd){
    free(bd->table);
    bd->table = NULL;
    
}


