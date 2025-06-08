#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "adress.h"
#include "graphe.h"
#include "trame.h"
#include "machine.h"
#include "bpdu.h"
#include "bridge.h"

void simulate_stp(graphe* g) {
    printf("\n====== Simulation STP =====\n");
    getchar();
    size_t nb_switch = g->nbSwitch;
    printf("Nombre de switches: %ld\n", nb_switch);

    int iterations = 0;
    const int max_iterations = 10;
    bool changed=true;

    while (changed){
        changed = false;
        printf("\n--- Itération %d ---\n", iterations + 1);
        for (size_t i = 0; i < nb_switch; i++) {
            bridge* br = (bridge*)g->sommets[i]->machine->machine;
            send_bdpu(br);
        }

        for (size_t i = 0; i < nb_switch; i++) {
            bridge* br = (bridge*)g->sommets[i]->machine->machine;
            for (size_t j = 0; j < br->nb_ports; j++) {
                if (br->ports[j] && br->ports[j]->type_changed) {
                    changed = true;
                    br->ports[j]->type_changed = false; 
                }
            }
        }
        
        iterations++;
        if (iterations >= max_iterations) {
            printf("\nlimite d'itérations atteinte sans convergence\n");
            break;
        }
        
    } ;

    if (iterations == max_iterations) {
        printf("\nlimite d'itérations atteinte sans convergence\n");
    } else {
        printf("\nTopologie stable après %d itérations\n", iterations);
    }

    printf("\nÉtat final des ports:\n");
    for (size_t i = 0; i < nb_switch; i++) {
        bridge* br = (bridge*)g->sommets[i]->machine->machine;
        printf("Switch %ld (%s):\n", i, to_string_mac(&br->addr_mac, (char[20]){0}));
        for (size_t j = 0; j < br->nb_ports; j++) {
            if (br->ports[j] && br->ports[j]->port) {
                interface* inter = br->ports[j]->port;
                printf("  Port %ld [", j);
                
                switch (br->ports[j]->type) {
                    case RACINE: printf("RACINE"); break;
                    case DESIGNE: printf("DESIGNE"); break;
                    case NONDESIGNE: printf("NONDESIGNE"); break;
                    default: printf("INCONNU");
                }
                
                printf("] -> Connecté à: ");
                
                if (inter->connected_to) {
                    machine* connected_machine = inter->connected_to->machine;
                    if (connected_machine->type == SWITCH) {
                        bridge* connected_br = (bridge*)connected_machine->machine;
                        printf("Switch %p (MAC: %s)", 
                            (void*)connected_machine,
                            to_string_mac(&connected_br->addr_mac, (char[20]){0}));
                    } else {
                        printf("Station %p (MAC: %s)", 
                            (void*)connected_machine,
                            to_string_mac(&connected_machine->addr_mac, (char[20]){0}));
                    }
                } else {
                    printf("Non connecté");
                }
                
                printf("\n");
            }
        }
    }
}

void quitter(graphe* g, FILE* file, char* lignes[], int nb_lignes){
    printf("\n===== Libération de la mémoire =====\n");
    desinit_graphe(g);
    close_file(file, lignes, nb_lignes);
}

void envoyer_trame(graphe* g){
    printf("\n===== Envoi de trame =====\n");
    for(int i =0;i<g->ordre;i++){
        printf("[%d] %s \n",i,to_string_mac(&(g->sommets[i]->machine->addr_mac),(char[50]){0}));
    }
    int index_machine1 = 0;
    int index_machine2 = 0;

    printf("Choisissez la machine qui enverra la trame : ");
    while(scanf("%d", &index_machine1) != 1){
        fprintf(stderr, "Erreur : entrée invalide.\n");
    }

    printf("Choisissez la destination de la trame : ");
    while(scanf("%d", &index_machine2) != 1){
        fprintf(stderr, "Erreur : entrée invalide.\n");
    }

    printf("La machine %d enverra une trame à la machine %d\n", index_machine1, index_machine2);

    printf("\n===== Envoi d'une trame entre machines =====\n");
    getchar();
    
    machine* station1 = g->sommets[index_machine1]->machine;
    machine* station2 = g->sommets[index_machine2]->machine;
    
    trame test_trame;
    size_t pong = 0;
    char msg_buffer[128];
    
    init_trame(&test_trame, station1->addr_mac, station2->addr_mac, &pong, PING);
    printf("De: %s\n", to_string_mac(&station1->addr_mac, (char[20]){0}));
    printf("À: %s\n", to_string_mac(&station2->addr_mac, (char[20]){0}));
    printf("Message: %s\n", to_string_message(&test_trame, msg_buffer));
    
    send_trame(station1, &test_trame, station1->interface);
    desinit_trame(&test_trame);
}

void afficher_table(graphe* g){
    printf("\n===== Affichage de la Table de commutation =====\n");
    if (g->ordre > 0) {
        for(int i =0;i<g->ordre;i++){
            printf("[%d] %s \n",i,to_string_mac(&(g->sommets[i]->machine->addr_mac),(char[50]){0}));
        }
        int index_switch = 0;
        printf("Choisissez le switch: ");
        if (scanf("%d", &index_switch) != 1) {
            fprintf(stderr, "Erreur : entrée invalide.\n");
        }
        else{
            print_switch_table((bridge*)g->sommets[index_switch]->machine->machine);
        }
    }
}

int main(int argc, char const *argv[]) {
    printf("\n===== Récupération de la configuration réseau =====\n");
    getchar();
    
    int MAX_LIGNES = 1024;
    FILE* file = open_file("triangle.lan");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return EXIT_FAILURE;
    }

    char* lignes[MAX_LIGNES];
    int nb_lignes = read_file(file, lignes);
    graphe g;
    parse_file(&g, lignes);

    int choix = -1;
    while(choix != 0){
        printf("\n========== Menu ==========\nQue souhaitez-vous faire ?\n");
        printf("0 - Quitter\n");
        printf("1 - Envoyer une trame\n");
        printf("2 - Afficher la table de commutation\n");
        printf("3 - Simuler le protocole STP\n");
        while(scanf("%d", &choix) != 1){
            fprintf(stderr, "Erreur : entrée invalide.\n");
        }
        switch(choix){
            case 1:
                envoyer_trame(&g);
                getchar();
                break;
            case 2:
                afficher_table(&g);
                getchar();
                break;
            case 3:
                simulate_stp(&g);
                getchar();
                break;
            default:
                break;
        }
    }
    quitter(&g, file, lignes, nb_lignes);
}