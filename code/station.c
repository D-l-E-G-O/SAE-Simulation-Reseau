#include station.h

void to_string_station(station st){
    printf("Adresse MAC: %s\n", to_string_mac(st.addr_mac));
    printf("Adresse IPV4: %s\n", to_string_ipv4(st.addr_ip));
}