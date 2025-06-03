#include <trame.h>
#include <stdio.h>
#include <stdlib.h>

void init_trame(trame * tra, mac source, mac dest, void* message, trame_type type){
    tra->dest =dest;
    tra->source = source;
    switch(type){
        case PING:
            ping p = *((ping*)message);
            tra->message = (ping*)(&p);
            break;
        case BPDU:
            bpdu b = *((bpdu*)message);
            tra->message = (bpdu*)(&b);
            break;
    }
    tra->type = type;
};

char* to_string_message(const trame* tra, char* buffer){
    switch(tra->type){
        case PING:
            sprintf(buffer, "Ping: %zu", *(ping*)tra->message);
            break;
        case BPDU:
            char str_bpdu[64];
            to_string_bpdu(*((bpdu*)tra->message), str_bpdu);
            sprintf(buffer, "BPDU: %s", str_bpdu);
            break;
    }
    return buffer;
}

void desinit_trame(trame* tra){
    switch(tra->type){
        case PING:
            free((ping*)tra->message);
            break;
        case BPDU:
            free((bpdu*)tra->message);
            break;
    }
    //free(tra);
}