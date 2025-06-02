#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"
#include "graphe.h"
#include "trame.h"  
#include "machine.h"

int main(int argc, char const *argv[]) {
        
    printf("\n=== Récupération de la configuration réseau ===\n");
    getchar();
    int MAX_LIGNES = 1024;
    FILE *file;
    file = open_file("mylan_no_cycle.lan");
    char* lignes[MAX_LIGNES];  
    int nb_lignes = read_file(file, lignes);
    graphe g;
    parse_file(&g , lignes);


    printf("\n=== Test d'envoi d'une trame entre machines ===\n");
    getchar();
    machine* station1 = g.sommets[7]->machine; 
    machine* station2 = g.sommets[13]->machine;
    trame test_frame;
    init_trame(&test_frame, station1->addr_mac,station2->addr_mac,0);    
    printf("De: %s\n", to_string_mac(&station1->addr_mac, (char[20]){0}));
    printf("À: %s\n", to_string_mac(&station2->addr_mac, (char[20]){0}));
    printf("Message: %d\n", test_frame.message);
    send_trame(station1, &test_frame,station1->interface);
    
    
    printf("\n=== Affichage de la Table de commutation ===\n");
    getchar();
    print_switch_table((bridge*)g.sommets[0]->machine->machine);


    printf("\n=== Libération de la mémoire ===\n");
    getchar();
    desinit_graphe(&g);
    close_file(file,lignes,nb_lignes);

    return 0;
}