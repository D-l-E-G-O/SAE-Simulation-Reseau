#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"
#include "graphe.h"
#include "trame.h"  
#include "machine.h"

int main(int argc, char const *argv[]) {
    int MAX_LIGNES = 1024;    
    printf("Démarrage du test réseau...\n");
    FILE *file;
    file = open_file("mylan_no_cycle.lan");
    char* lignes[MAX_LIGNES];  
    int nb_lignes = read_file(file, lignes);
    graphe g;
    parse_file(&g , lignes);


    machine* station1 = g.sommets[7]->machine; 
    machine* station2 = g.sommets[13]->machine; 
    getchar();
    trame test_frame;
    init_trame(&test_frame, station1->add_mac,station2->add_mac,0);               
   getchar();
    printf("\n=== Envoi d'une trame de test ===\n");
    printf("De: %s\n", to_string_mac(&station1->add_mac, (char[20]){0}));
    printf("À: %s\n", to_string_mac(&station2->add_mac, (char[20]){0}));
    printf("Message: %d\n", test_frame.message);
    getchar();
    
    send_trame(station1, &test_frame,station1->interface);
    

    print_switch_table((bridge*)g.sommets[0]->machine->machine);

    desinit_graphe(&g);

    close_file(file,lignes,nb_lignes);
    return 0;
}