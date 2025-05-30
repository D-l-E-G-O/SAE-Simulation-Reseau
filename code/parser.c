#pragma one                                                                     
#include "parser.h"                                                             
#include <string.h>                                                             
#include <stdlib.h>  

#include <station.h>
#include <bridge.h>
#include <interface.h>
                                                                                
int MAX_LIGNE_SIZE = 1024;                                                           
int MAX_LIGNE = 1024;                                                          
                                                                                
FILE* open_file(char * nameFile){                                               
    return fopen(nameFile,"r");                                                 
};                                                                              
                                                                                
int read_file(FILE* file, char* lignes[]) {                                     
    if (file == NULL) {                                                         
        return -1;                                                              
    }                                                                           
                                                                                
    char buffer[MAX_LIGNE_SIZE];                                                     
    int count = 0;                                                              
                                                                                
    while (fgets(buffer, MAX_LIGNE_SIZE, file) != NULL && count < MAX_LIGNE) {      
        buffer[strcspn(buffer, "\n")] = '\0';                                   
                                                                                
        lignes[count] = malloc(strlen(buffer) + 1);                             
        if (lignes[count] == NULL) {                                            
            return -1;                                                          
        }                                                                       
        strcpy(lignes[count], buffer);                                          
        count++;                                                                
    }                                                                  
                                                                                
    return count;                                                               
}     



int close_file(FILE* file, char* lignes[], int nb_lignes) {
    if (file != NULL) {
        fclose(file);
    }
    
    if (lignes != NULL) {
        for (int i = 0; i < nb_lignes; i++) {
            free(lignes[i]); 

        }
    }
    
    return 0;
}                                                                    
                                                                                
void parse_file(graphe *g, char* ligne[]) {
    int nb_machine = 0;
    int nb_connexion = 0;
    sscanf(ligne[0], "%d %d", &nb_machine, &nb_connexion);
    printf("nb machine : %d nb connexion : %d\n", nb_machine, nb_connexion);
    init_graphe(g,nb_machine);
    for(int i = 1; i <= nb_machine; i++) {
        int type;
        char buffer[MAX_LIGNE_SIZE];
        sscanf(ligne[i], "%d;%[^\n]", &type, buffer);

        if(type == STATION) {
            char macAddr[18];  
            char ipAddr[16];  
            sscanf(buffer, "%[^;];%15s", macAddr, ipAddr);
            printf("Station: MAC=%s, IP=%s\n", macAddr, ipAddr);
            station* sta = malloc(sizeof(station)) ;
            mac mac = string_to_mac(macAddr);
            ipv4 ip = string_to_ipv4(ipAddr);
            init_station(sta,mac,ip);
            interface* inter = malloc(sizeof(interface));
            add_interface_station(sta,inter);
        }
        else if(type == SWITCH) {
            char macAddr[18];
            int nb_port, priorite;
            sscanf(buffer, "%[^;];%d;%d", macAddr, &nb_port, &priorite);
            printf("Switch: MAC=%s, Ports=%d, Priorite=%d\n", macAddr, nb_port, priorite);
            bridge  * bridge = malloc(sizeof(bridge));
            mac mac = string_to_mac(macAddr);
            init_bridge(bridge,mac,nb_port,priorite);
            interface* inter = malloc(sizeof(interface));
            add_interface_bridge(bridge,inter);
        }
    }

    for(int i = nb_machine + 1; i <= nb_machine + nb_connexion; i++) {
        int type, indexmachine1, indexmachine2;
        sscanf(ligne[i], "%d;%d;%d", &type, &indexmachine1, &indexmachine2);
        printf("Connexion entre %d et %d\n", indexmachine1, indexmachine2);
        machine * machine1 = g->sommets[indexmachine1].machine;
        machine * machine2 = g->sommets[indexmachine2].machine;
        connect_two_machine(machine1,machine2);
    }
}                                                           
                                                                                
                                                                                




