#pragma one                                                                     
#include <graphe.h>                                                          
#include <stdlib.h>                                                             
#include <stdio.h>                                                              
                                                                                
                                                                                
                                                                                
void init_graphe(graphe *g, int nbSommet) {                                       
    g->matrice = (poids**)malloc(nbSommet * sizeof(poids*));                  
    g->sommets = (sommet**)malloc(nbSommet * sizeof(sommet*));                    
    g->ordre = nbSommet;                                                       
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

void init_sommet(sommet *s , int index,machine * machine){
    s->index = index;
    s->machine = machine;
};


void add_sommet(graphe* g,sommet* sommet,int index){
    g->sommets[index] = sommet;
};


              
                                                                                
void desinit_graphe(graphe *g){                                     
                                                                                
    for (int i = 0; i < g->ordre; i++) {                                        
        free(g->matrice[i]);                                                  
        g->matrice[i] =NULL; 
        desinit_sommet(g->sommets[i]);  
        free(g->sommets[i]);
        g->matrice[i] =NULL;                                               
    }                       
                                                        
    free(g->matrice);                                                         
    free(g->sommets);                                                           
    g->matrice = NULL;                                                        
    g->sommets =NULL;      
    g = NULL;                                                     
}                                                                               
       

void desinit_sommet(sommet *s){
    s->index =-1;
    desinit_machine(s->machine);
    free(s->machine);
    s->machine = NULL;
};
                                                                                                                                                            
                                                                                
void add_vertex(graphe *g,sommet a , sommet b , int poids ){                                   
    g->matrice[a.index][b.index] = poids ;                                       
};                                                                              
                                                                                
                                                                  
                                                                                
                                                                                
char* to_string_graphe(const graphe* g, char* buffer) {
    if (!g || !buffer) return NULL;
    int pos = 0;
    buffer[0] = '\0'; 
    for (int i = 0; i < g->ordre; ++i) {
        pos += sprintf(buffer + pos, "   %c", 'A' + i);
    }
    for (int i = 0; i < g->ordre; ++i) {
        pos += sprintf(buffer + pos, "\n%c", 'A' + i); 
        for (int j = 0; j < g->ordre; ++j) {
            pos += sprintf(buffer + pos, "  %ld", g->matrice[i][j]); 
        }
    }
    buffer[pos] = '\n';
    return buffer;
}

char* to_string_sommet(const sommet* sommet,char* buffer);                                   
                                                                                
void afficher_matrice();                                                        
void afficher_sommet();                                                         