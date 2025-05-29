#include <trame.h>

void init_trame(trame * tra,mac source,mac dest){
    tra->dest =dest;
    tra->source = source;
    tra->message =4;
};

void send_trame_between_two_sommet(sommet* s1,sommet* s2){
    if(s1->type == SWITCH){
    }
    if(s2->type == STATION){
        
    }
};