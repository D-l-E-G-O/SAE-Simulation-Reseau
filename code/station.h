#pragma once
#include <adress.h>
#include <trame.h>

typedef struct station
{
    mac addr_mac;
    ipv4 addr_ip;

}station;


void init_station(station * sta,mac addrmac,ipv4 ip);

void desinit_station(station *sta);

char* to_string_station(station* st,char*  buffer);

bool is_for_me_question_mark(station *sta,trame* t);


