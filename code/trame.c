#include <trame.h>

void init_trame(trame * tra,mac source,mac dest){
    tra->dest =dest;
    tra->source = source;
    tra->message =4;
};
