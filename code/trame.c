#include <trame.h>

void init_trame(trame * tra, mac source, mac dest, size_t message){
    tra->dest =dest;
    tra->source = source;
    tra->message =message;
};
