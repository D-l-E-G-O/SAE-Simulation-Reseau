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
    printf("\n====== Simulation STP ==================\n");
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

int main(int argc, char const *argv[]) {

     
    
    printf("\n=== Récupération de la configuration réseau ===\n");
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

    // Simulation du protocole STP
    simulate_stp(&g);


    printf("======ENVOIE DE TRAME======\n");
    for(int i =0;i<g.ordre;i++){
        printf("[%d] %s \n",i,to_string_mac(&g.sommets[i]->machine->addr_mac,(char[50]){0}));
    }
    int index_machine1 = 0;
    int index_machine2 = 0;

    printf("Choisissez la machine qui enverra la trame : ");
    if (scanf("%d", &index_machine1) != 1) {
        fprintf(stderr, "Erreur : entrée invalide.\n");
        return 1;
    }

    printf("Choisissez la destination de la trame : ");
    if (scanf("%d", &index_machine2) != 1) {
        fprintf(stderr, "Erreur : entrée invalide.\n");
        return 1;
    }

    printf("La machine %d enverra une trame à la machine %d\n", index_machine1, index_machine2);
    getchar();


    //Test de communication
    printf("\n=== Test d'envoi d'une trame entre machines ===\n");
    getchar();
    
    machine* station1 = g.sommets[index_machine1]->machine;
    machine* station2 = g.sommets[index_machine2]->machine;
    

    
    trame test_trame;
    size_t pong = 0;
    char msg_buffer[128];
    
    init_trame(&test_trame, station1->addr_mac, station2->addr_mac, &pong, PING);
    printf("De: %s\n", to_string_mac(&station1->addr_mac, (char[20]){0}));
    printf("À: %s\n", to_string_mac(&station2->addr_mac, (char[20]){0}));
    printf("Message: %s\n", to_string_message(&test_trame, msg_buffer));
    
    send_trame(station1, &test_trame, station1->interface);
    desinit_trame(&test_trame);

    printf("\n=== Affichage de la Table de commutation ===\n");
    getchar();
    if (g.ordre > 0) {
        print_switch_table((bridge*)g.sommets[1]->machine->machine);
    }

    printf("\n=== Libération de la mémoire ===\n");
    getchar();
    desinit_graphe(&g);
    close_file(file, lignes, nb_lignes);

}