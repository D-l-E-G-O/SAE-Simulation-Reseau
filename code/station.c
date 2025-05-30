#include <station.h>
#include <stdlib.h>
void init_station(station * sta,mac addrmac,ipv4 ip){
    sta->addr_mac = addrmac;
    sta->addr_ip = ip;
    sta->interface = (interface*)malloc(sizeof(interface)); 
}


void add_interface_station(station * sta,interface* inter){
    sta->interface = inter;
};

void desinit_station(station *sta){
    sta->addr_mac = 0;
    sta->addr_ip = 0;
    free(sta->interface);
    sta->interface = NULL;
};

char* to_string_station(station* sta,char*  buffer){
    return buffer;
};


bool is_for_me_question_mark(station *sta,trame* t){
    return(compare_mac(&sta->addr_mac,&t->dest));
}

