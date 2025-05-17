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
