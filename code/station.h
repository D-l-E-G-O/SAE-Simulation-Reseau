#pragma once
#include <adress.h>
#include <trame.h>
#include <interface.h>

typedef struct station
{
    mac addr_mac;
    ipv4 addr_ip;
    interface* interface;

}station;


void init_station(station * sta,mac addrmac,ipv4 ip);

void add_interface_station(station * sta,interface* inter);

void desinit_station(station *sta);

char* to_string_station(station* st,char*  buffer);

bool is_for_me_question_mark(station *sta,trame* t);


