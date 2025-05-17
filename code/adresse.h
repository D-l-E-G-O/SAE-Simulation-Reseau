#pragma once
#include <stdint.h> 
#include <stdbool.h>
typedef uint8_t mac[6];

typedef uint32_t ipv4;

bool compare_mac(const mac mac1,const mac mac2);
void to_string_mac(const mac mac,char * buffer);

bool compare_ipv4(const ipv4 ip1,const ipv4 ip2);
bool to_string_ipv4(const ipv4 ip,char * buffer);


