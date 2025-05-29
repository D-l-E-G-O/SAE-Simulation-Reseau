#pragma once
#include <stddef.h>


typedef size_t poids;

#define NONE ((poids)0)

typedef enum{
    STATION = 1,
    SWITCH = 2,
}type;


typedef struct sommet
{
    int index;
    void* machine;
    type type;
}sommet;


typedef struct graphe
{
    poids** matrice;
    sommet* sommets;
    int ordre;
}graphe;

void init_graphe(graphe *m,int nbSommet);
void init_sommet();
void desinit_graphe(graphe *m, int nbSommet);
void desinit_sommet();


void add_vertex(graphe *m,sommet a , sommet b,int poids );

char* to_string_sommet(const sommet* sommet,char * buffer);
char* to_string_graphe(const graphe* matrice,char* buffer);


void afficher_matrice();
void afficher_sommet();
