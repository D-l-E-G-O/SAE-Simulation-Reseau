#pragma once
#include <adresse.h>

typedef struct station
{
    mac addr_mac;
    ipv4 addr_ip;
};

void to_string_station(station st);

