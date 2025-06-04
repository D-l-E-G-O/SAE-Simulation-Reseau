#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include "adress.h"
#include "graphe.h"
#include "trame.h"  
#include "machine.h"
#include <bpdu.h>
#include <bridge.h>

int main(int argc, char const *argv[]) {
        
    printf("\n=== Récupération de la configuration réseau ===\n");
    getchar();
    int MAX_LIGNES = 1024;
    FILE *file;
    file = open_file("mylan.lan");
    char* lignes[MAX_LIGNES];  
    int nb_lignes = read_file(file, lignes);
    graphe g;
    parse_file(&g , lignes);


    printf("\n======SETUP STP==================");
    getchar();
    printf("il y a %ld switch ",g.nbSwitch);
    size_t nb_switch = g.nbSwitch;
    for(size_t i =0;i<nb_switch;i++){
        bridge *  switchi =(bridge * ) g.sommets[i]->machine->machine;
        bpdu bpdui;
        trame bpduTrame;
        init_bpdu(&bpdui,switchi->priorite,switchi->addr_mac);
        init_trame(&bpduTrame,switchi->addr_mac,switchi->addr_mac,&bpdui,BPDU);
        file_append(switchi,bpduTrame);
        trame tr = file_pop(switchi);
        desinit_trame(&tr);
    }
    size_t etat_switch =  (1 << nb_switch) - 1;
    printf("%ld \n",etat_switch);
    while (etat_switch!=0)
    {
        
        for(size_t i =0;i<nb_switch;i++){
            etat_switch &= ~(1 << i);
            printf("etat : %ld  \n",etat_switch);
            
        }
    }
    

    // getchar();
    // printf("\n=== Test d'envoi d'une trame entre machines ===\n");
    // getchar();
    // machine* station1 = g.sommets[7]->machine; 
    // machine* station2 = g.sommets[13]->machine;
    // trame test_trame;
    // size_t pong = 0;
    // char msg_buffer[128];
    // init_trame(&test_trame, station1->addr_mac,station2->addr_mac,&pong, PING);    
    // printf("De: %s\n", to_string_mac(&station1->addr_mac, (char[20]){0}));
    // printf("À: %s\n", to_string_mac(&station2->addr_mac, (char[20]){0}));
    // printf("Message: %s\n", to_string_message(&test_trame, msg_buffer));
    // send_trame(station1, &test_trame,station1->interface);
    // desinit_trame(&test_trame);

    printf("\n=== Affichage de la Table de commutation ===\n");
    getchar();
    print_switch_table((bridge*)g.sommets[0]->machine->machine);


    printf("\n=== Libération deux là mémoireuh ===\n");
    getchar();
    desinit_graphe(&g);
    close_file(file,lignes,nb_lignes);

    return 0;
}