#include <stdio.h>
#include <stdlib.h>

#define NUM_FILAS 8
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

//VARIABLES GLOBALES
	int globaltime = 0;
	int numfallos = 0;
	unsigned char Simul_RAM[4096];


int main(int argc, char* argv[]){
	
	//Crear las variables
	T_LINEA_CACHE linea_cache[NUM_FILAS];
	
	int variable1 = 0xFF;
	int variable2 = 0x23F;
	
	//Llamar a las funciones
	LimpiaCACHE(linea_cache);
	VuelcaCACHE(linea_cache);
	
	return 0;
}

int cambioHexadecimalADecimal(int variable1, int variable2){
	
	if(isdigit(variable1, variable2)){
		return variable1, variable2 - '0';
		
	}
	
	return 0;
}

void LimpiaCACHE(T_LINEA_CACHE *tbl){
	
	for(int i=0;i<NUM_FILAS; i++){
		
		 tbl[i].ETQ = 0xFF;
		for(int j=0; j<TAM_LINEA; j++){
			tbl[i].Datos[j]=0x23F;
		}
	}
}

void VuelcaCACHE(T_LINEA_CACHE *tbl){
	
	for(int i=0;i<NUM_FILAS; i++){
		
		printf("ETQ: %02X  Data ", tbl[i].ETQ);
		for(int j=0; j<TAM_LINEA; j++){
			printf("%02X ", tbl[i].Datos[j]);
		}
	}
}