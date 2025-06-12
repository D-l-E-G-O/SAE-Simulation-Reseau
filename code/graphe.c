#include <graphe.h>                                                          
#include <stdlib.h>                                                             
#include <stdio.h>                                                              
                                                                                
                                                                                
                                                                                
void init_graphe(graphe *g, int nbSommet) {
    // Procédure qui initialise le graphe.                                  
    g->matrice = (poids**)malloc(nbSommet * sizeof(poids*));                  
    g->sommets = (sommet**)malloc(nbSommet * sizeof(sommet*));                    
    g->ordre = nbSommet;           
    g->nbSwitch =0;
    g->nbStation=0;                                            
    if (g->matrice == NULL || g->sommets == NULL) {                           
        printf("Error malloc");                                                 
    }                                                                           
                                                                                
    for (int i = 0; i < nbSommet; i++) {                                        
        g->matrice[i] = (poids*)malloc(nbSommet * sizeof(poids));             
        if (g->matrice[i] == NULL) {                                          
            printf("Error malloc");                                             
        }                                                                       
                                                                                
        for (int j = 0; j < nbSommet; j++) {                                    
            g->matrice[i][j] = NONE;                                          
        }                                                                       
    }                                                                           
}     

void init_sommet(sommet *s , int index, machine * machine){
    // Procédure qui initialise un sommet.
    s->index = index;
    s->machine = machine;
}


void add_sommet(graphe* g,sommet* sommet,int index){
    // Procédure qui ajoute un sommet au graphe.
    g->sommets[index] = sommet;
}


              
                                                                                
void desinit_graphe(graphe *g){                                     
    // Procédure qui libère la mémoire allouée par le graphe.                                              
    for (int i = 0; i < g->ordre; i++) {                                        
        free(g->matrice[i]);                                                  
        g->matrice[i] =NULL; 
        desinit_sommet(g->sommets[i]);  
        free(g->sommets[i]);
        g->matrice[i] =NULL;                                               
    }                       
                                                        
    free(g->matrice);                                                         
    free(g->sommets);   
    g->nbStation =0;
    g->nbSwitch = 0;                                                        
    g->matrice = NULL;                                                        
    g->sommets =NULL;      
    g = NULL;                                                     
}                                                                               
       

void desinit_sommet(sommet *s){
    // Procédure qui libère la mémoire allouée par le sommet.
    s->index =-1;
    desinit_machine(s->machine);
    free(s->machine);
    s->machine = NULL;
}
                                                                                                                                                                                                                