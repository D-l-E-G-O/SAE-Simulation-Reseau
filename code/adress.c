#pragma one
#include "adress.h"


bool compare_mac(mac const* mac1, mac const* mac2){
    bool equal = true;
    size_t i = 0;
    while(i<6 && equal){
        equal = (mac1[i]&mac2[i] == mac1[i]);
    }
    return equal;
};

char* to_string_mac(mac const* mac, char * buffer){

};

void afficher_mac(mac const* mac);




bool compare_ipv4( ipv4 const* ip1, ipv4 const* ip2){
    return ip1&ip2 == ip1;
};

char* to_string_ipv4(ipv4 const* ip, char* buffer){
    for(size_t i=1; i<=4; i++){
        u_int32_t masque = (1 << (i*8)) - 1;
        uint8_t x = (ip&masque) >> (32 - i*8);
        if (i<4){
            sprintf(buffer, "%zu.", x);
        }
        else{
            sprintf(buffer, "%zu", x);
        }
    }
};

void afficher_ip(ipv4 const *ip){
    printf("IPV4: %s", to_string_ipv4(ip));
};


