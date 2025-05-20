#pragma once
#include <stdint.h> 
#include <stdbool.h>
typedef uint8_t mac[6];

typedef uint32_t ipv4;

void init_mac();
void init_ipv4();

bool compare_mac(mac const * mac1, mac const* mac2);
char* to_string_mac(mac const * mac,char * buffer);

bool compare_ipv4( ipv4 const* ip1, ipv4 const* ip2);
char* to_string_ipv4(ipv4 const * ip,char * buffer);


void afficher_mac( mac const* mac);
void afficher_ip(ipv4 const  *ip);


