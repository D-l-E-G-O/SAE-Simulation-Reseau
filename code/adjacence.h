#pragma once

typedef size_t poids;

typedef enum{
    MACHINE = 1,
    SWITCH = 2,
}type;


typedef struct sommet
{
    void* machine;
    type type;
    poids* poids;
}sommet;


typedef struct matrice_adj
{
    poids** adjacence;
    sommet* sommets;
}adj;

void init_matrice();
void init_sommet();


char* to_string_matrice(const matrice_adj* matrice);
char* to_string_sommet(const sommet* sommet);

void afficher_matrice();
void afficher_sommet();
