#pragma one
#include <stdio.h>
#include "graphe.h"

FILE* open_file(char * nameFile);
 
int read_file(FILE  *file,char* lignes[]);

int close_file(FILE * file);

void parse_file(graphe *g,char* lignes[]);

