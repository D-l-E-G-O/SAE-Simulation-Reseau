#pragma once
#include <stddef.h>
#include <stdlib.h> 
#include <machine.h>


typedef size_t poids;

#define NONE ((poids)0)


typedef struct sommet
{
    int index;
    machine* machine;
}sommet;

typedef struct graphe
{
    poids** matrice;
    sommet** sommets;
    int ordre;
}graphe;

void init_graphe(graphe *m,int nbSommet);
void init_sommet(sommet * s, int index,machine * machine);
void desinit_graphe(graphe *g);
void desinit_sommet(sommet *s);


void add_vertex(graphe *m,sommet a , sommet b,int poids );
void add_sommet(graphe *g,sommet *s,int index);
char* to_string_sommet(const sommet* sommet,char * buffer);
char* to_string_graphe(const graphe* matrice,char* buffer);


void afficher_matrice(const graphe* g);
void afficher_sommet();
