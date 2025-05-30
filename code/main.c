#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"

#include "graphe.h"
int main(int argc, char const *argv[])
{
    int MAX_LIGNES = 1024;    
    printf("hellozeze world\n");
    FILE *file;
    file = open_file("mylan_no_cycle.lan");
    char* lignes[MAX_LIGNES];  
    int nb_lignes = read_file(file, lignes);
    graphe g;
    parse_file(&g , lignes);
    close_file(file,lignes,nb_lignes);
    desinit_graphe(&g);
    
    return 0;
}