#include <trame.h>
#include <stdio.h>
#include <stdlib.h>

void init_trame(trame * tra, mac source, mac dest, void* message, trame_type type){
    tra->dest = dest;
    tra->source = source;
    tra->type = type;

    switch(type){
        case PING:
            tra->message = malloc(sizeof(ping));
            if (tra->message == NULL) exit(EXIT_FAILURE);
            *((ping*)tra->message) = *((ping*)message);
            break;
        case BPDU:
            tra->message = malloc(sizeof(bpdu));
            if (tra->message == NULL) exit(EXIT_FAILURE);
            *((bpdu*)tra->message) = *((bpdu*)message);
            break;
    }
}


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
        case BPDU:
            free(tra->message);
            break;
    }
}


void copy_trame(trame* dest, const trame* src) {
    init_trame(dest, src->source, src->dest, src->message, src->type);
}
