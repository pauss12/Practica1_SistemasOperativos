#include <stdio.h>
#include <stdlib.h>

#define NUM_FILAS 6
#define MAX_LINE 100
#define TAM_LINEA 8
#define LRAM 1024

typedef struct {
	
	unsigned short int ETQ;
	char Datos[TAM_LINEA];
	
}T_LINEA_CACHE;

void LimpiaCACHE(T_LINEA_CACHE tbl[NUM_FILAS]);
void VuelcaCACHE(T_LINEA_CACHE *tbl);
void Parseaaddr(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TrataFallo(T_LINEA_CACHE *tbl, char *MRAM, int ETQ, int linea, int bloque);

int main(int argc, char* argv[]){
	
	return 0;
}