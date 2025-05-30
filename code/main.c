#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"
#include "graphe.h"
#include "trame.h"  // Pour les fonctions de trame
#include "machine.h" // Pour send_trame

int main(int argc, char const *argv[]) {
    int MAX_LIGNES = 1024;    
    printf("Démarrage du test réseau...\n");
    FILE *file;
    file = open_file("reseau.txt");
    char* lignes[MAX_LIGNES];  
    int nb_lignes = read_file(file, lignes);
    graphe g;
    parse_file(&g , lignes);


    machine* station1 = g.sommets[2]->machine; 
    machine* station2 = g.sommets[3]->machine; 
    printf("la machine 2 est connecté a %s\n",to_string_mac(&station1->interface->connected_to->machine->add_mac, (char[20]){0}));
    trame test_frame;
    init_trame(&test_frame, station1->add_mac,station2->add_mac,0);               

    printf("\n=== Envoi d'une trame de test ===\n");
    printf("De: %s\n", to_string_mac(&station1->add_mac, (char[20]){0}));
    printf("À: %s\n", to_string_mac(&station2->add_mac, (char[20]){0}));
    printf("Message: %d\n", test_frame.message);
    
    send_trame(station1, &test_frame,station1->interface);
    

    print_switch_table((bridge*)g.sommets[0]->machine->machine);

    desinit_graphe(&g);

    close_file(file,lignes,nb_lignes);
    return 0;
}