#pragma once 
#include <adress.h>
#include <graphe.h>
#include <commutateur.h>

//@destination @source type données bourrage FCS


typedef struct trame{
    mac source;
    mac dest;
    int message;
}trame;

void init_trame(trame * tra,mac source,mac dest);

void send_trame_between_two_sommet(sommet* s1,sommet* s2);