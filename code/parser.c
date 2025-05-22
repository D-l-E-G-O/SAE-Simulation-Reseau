#pragma one                                                                     
#include "parser.h"                                                             
#include <string.h>                                                             
#include <stdlib.h>  
                                                                                
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






                                                                                
int close_file(FILE * file){                                                    
    fclose(file);                                                               
};                                                                              
                                                                                
void parse_file(graph *g, char* ligne[]) {
    int nb_machine = 0;
    int nb_connexion = 0;
    sscanf(ligne[0], "%d %d", &nb_machine, &nb_connexion);
    printf("nb machine : %d nb connexion : %d\n", nb_machine, nb_connexion);

    for(int i = 1; i <= nb_machine; i++) {
        int type;
        char buffer[MAX_LIGNE_SIZE];
        sscanf(ligne[i], "%d;%[^\n]", &type, buffer);

        if(type == STATION) {
            char macAddr[18];  
            char ipAddr[16];  
            sscanf(buffer, "%[^;];%15s", macAddr, ipAddr);
            printf("Station: MAC=%s, IP=%s\n", macAddr, ipAddr);
        }
        else if(type == SWITCH) {
            char macAddr[18];
            int nb_port, priorite;
            sscanf(buffer, "%[^;];%d;%d", macAddr, &nb_port, &priorite);
            printf("Switch: MAC=%s, Ports=%d, Priorite=%d\n", macAddr, nb_port, priorite);
        }
    }

    for(int i = nb_machine + 1; i <= nb_machine + nb_connexion; i++) {
        int type, machine1, machine2;
        sscanf(ligne[i], "%d;%d;%d", &type, &machine1, &machine2);
        printf("Connexion entre %d et %d\n", machine1, machine2);
    }
}                                                            
                                                                                
                                                                                




