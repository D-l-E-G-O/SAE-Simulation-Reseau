#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"

#include "graphe.h"
int main(int argc, char const *argv[])
{
    // int MAX_LIGNES = 1024;    
    // printf("hellozeze world\n");
    // FILE *file;
    // file = open_file("mylan_no_cycle.lan");
    // char* lignes[MAX_LIGNES];  
    // int nb_lignes = read_file(file, lignes);
    // close_file(file);
    // graph g;
    // parse_file(&g , lignes);


    graphe g;
    init_graphe(&g,10);
    printf("Example %ld\n",g.matrice[9][9]);
    char buffer[1024] = {'\0'};
    printf("%sazertyu\n" , to_string_graphe(&g,buffer));



    init_graphe(&g,10);
    


    printf("Test IPV4\n");
    ipv4 ip = string_to_ipv4("130.79.80.8");
    afficher_ipv4(&ip);
    return 0;
}