#include <trame.h>

void init_trame(trame * tra,mac source,mac dest,int message){
    tra->dest =dest;
    tra->source = source;
    tra->message =message;
};
