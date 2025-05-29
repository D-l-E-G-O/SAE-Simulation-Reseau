#include <station.h>

void init_station(station * sta,mac addrmac,ipv4 ip){
    sta->addr_mac = addrmac;
    sta->addr_ip = ip;
};


void desinit_station(station *sta){
    sta->addr_mac = 0;
    sta->addr_ip = 0;
};

char* to_string_station(station* sta,char*  buffer){
    return buffer;
};


bool is_for_me_question_mark(station *sta,trame* t){
    return(compare_mac(&sta->addr_mac,&t->dest));
}

