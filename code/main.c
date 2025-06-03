#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"
#include "graphe.h"
#include "trame.h"  
#include "machine.h"
#include <bpdu.h>

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
    trame test_trame;
    size_t pong = 0;
    char msg_buffer[128];
    init_trame(&test_trame, station1->addr_mac,station2->addr_mac,&pong, PING);    
    printf("De: %s\n", to_string_mac(&station1->addr_mac, (char[20]){0}));
    printf("À: %s\n", to_string_mac(&station2->addr_mac, (char[20]){0}));
    printf("Message: %s\n", to_string_message(&test_trame, msg_buffer));
    send_trame(station1, &test_trame,station1->interface);
    
    
    printf("\n=== Affichage de la Table de commutation ===\n");
    getchar();
    print_switch_table((bridge*)g.sommets[0]->machine->machine);


    printf("\n=== Test BPDU ===\n");
    getchar();
    bpdu bpdu;
    init_bpdu(&bpdu, 1, station1->addr_mac);
    char buffer[20];
    to_string_mac(&station1->addr_mac, buffer);
    printf("Création BPDU: [%s,0,%s]\n",buffer, buffer);
    char string_bpdu[64];
    to_string_bpdu(bpdu, string_bpdu);
    printf("to_string_bpdu: %s\n", string_bpdu);
    size_t int_bpdu = to_int_string_bpdu(string_bpdu);
    printf("to_int_string_bpdu: %zu\n", int_bpdu);
    char new_string_bpdu[64];
    to_string_int_bpdu(int_bpdu, new_string_bpdu);
    printf("to_string_int_bpdu: %s\n", new_string_bpdu);


    printf("\n=== Libération de la mémoire ===\n");
    getchar();
    desinit_graphe(&g);
    close_file(file,lignes,nb_lignes);

    return 0;
}