#pragma one
#include "adress.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>


bool compare_mac(mac const* mac1, mac const* mac2){
    return (*mac1&*mac2) == *mac1;
};

char* to_string_mac(mac const* mac, char * buffer){
    for(size_t i=12; i>0; i--){
        size_t nb_bits = (i-1)*5;
        uint16_t masque = 15 << nb_bits;
        uint8_t x = (*mac&masque) >> nb_bits;
        char* buff_temp = buffer;
        if (i==12){
            sprintf(buffer, "%u", x);
        }
        else{
            sprintf(buff_temp + strlen(buffer), ".%u", x);
        }
    }
    return buffer;
};

void afficher_mac(mac const* mac){
    char buffer[18];
    printf("MAC: %s\n", to_string_mac(mac, buffer));
}




ipv4 build_ipv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4){
    return (o1<<24) + (o2<<16) + (o3<<8) + o4; 
}

bool compare_ipv4( ipv4 const* ip1, ipv4 const* ip2){
    return (*ip1&*ip2) == *ip1;
};

char* to_string_ipv4(ipv4 const* ip, char* buffer){
    for(size_t i=4; i>0; i--){
        size_t nb_bits = (i-1)*8;
        uint32_t masque = 255 << nb_bits;
        uint8_t x = (*ip&masque) >> nb_bits;
        char* buff_temp = buffer;
        if (i==4){
            sprintf(buffer, "%u", x);
        }
        else{
            sprintf(buff_temp + strlen(buffer), ".%u", x);
        }
    }
    return buffer;
};

void afficher_ipv4(ipv4 const *ip){
    char buffer[16];
    printf("IPV4: %s\n", to_string_ipv4(ip, buffer));
};


