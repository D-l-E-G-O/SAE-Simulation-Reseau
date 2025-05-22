#pragma one
#include <stdio.h>
#include "graph.h"

FILE* open_file(char * nameFile);
 
int read_file(FILE  *file,char* lignes[]);

int close_file(FILE * file);

void parse_file(graph *g,char* lignes[]);

