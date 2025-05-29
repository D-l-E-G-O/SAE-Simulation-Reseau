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

mac string_to_mac(char* string) {
    if (string == NULL) {
        return 0;
    }
    
    unsigned int o1, o2, o3, o4, o5, o6;
    if (sscanf(string, "%02x:%02x:%02x:%02x:%02x:%02x", 
               &o1, &o2, &o3, &o4, &o5, &o6) != 6) {
        return 0; //EROROROROROROROROROR
    }
    
    return ((mac)o1 << 40) | ((mac)o2 << 32) | ((mac)o3 << 24) | 
           ((mac)o4 << 16) | ((mac)o5 << 8) | (mac)o6;
};


ipv4 string_to_ipv4(char* string) {
    if (string == NULL) {
        return 0;
    }
    
    unsigned int o1, o2, o3, o4;
    if (sscanf(string, "%u.%u.%u.%u", &o1, &o2, &o3, &o4) != 4) {
        return 0; //EOROROROROROROROR;
    }
    
    if (o1 > 255 || o2 > 255 || o3 > 255 || o4 > 255) {
        return 0;//EOROROROROROROROR
    }
    
    return (o1 << 24) | (o2 << 16) | (o3 << 8) | o4;
}