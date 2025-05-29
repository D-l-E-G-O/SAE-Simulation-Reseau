#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"

int main(int argc, char const *argv[])
{
    int MAX_LIGNES = 1024;    
    printf("hellozeze world\n");
    FILE *file;
    file = open_file("mylan_no_cycle.lan");
    char* lignes[MAX_LIGNES];  
    int nb_lignes = read_file(file, lignes);
    close_file(file);
    graph g;
    parse_file(&g , lignes);

    printf("Test IPV4\n");
    ipv4 ip = build_ipv4(128,64,11,2);
    afficher_ipv4(&ip);
    return 0;
}