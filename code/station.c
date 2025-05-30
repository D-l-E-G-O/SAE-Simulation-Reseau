#include <station.h>
#include <stdlib.h>
#include <stdio.h>
void init_station(station * sta,ipv4 ip){
    sta->addr_ip = ip;
}



void desinit_station(station *sta){
    sta->addr_ip = 0;
};

char* to_string_station(station* sta,char*  buffer){
    return buffer;
};


