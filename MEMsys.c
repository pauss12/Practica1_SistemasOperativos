//INCLUIMOS TODAS LAS LIBRERIAS QUE NECESITEMOS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

//CREAMOS LOS DEFINE ----------------------------------------------------------------------------------------------------------------
#define NUM_FILAS 8
#define MAX_LINEA 100
#define TAM_LINEA 8
#define LRAM 1024

//ESTRUCTURA ----------------------------------------------------------------------------------------------------------------
typedef struct {
	
	unsigned short int ETQ;
	char Datos[TAM_LINEA];
	
}T_LINEA_CACHE;

//PROTOTIPOS DE LAS FUNCIONES ----------------------------------------------------------------------------------------------------------------
void LimpiaCACHE(T_LINEA_CACHE tbl[NUM_FILAS]);
void VuelcaCACHE(T_LINEA_CACHE *tbl);
void Parseaaddr(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TrataFallo(T_LINEA_CACHE *tbl, char *MRAM, int ETQ, int linea, int bloque);
int cambioHexadecimalADecimal(long long numero );

//VARIABLES GLOBALES ----------------------------------------------------------------------------------------------------------------
	int globaltime = 0;
	int numfallos = 0;
	unsigned char Simul_RAM[4096];

//MAIN ----------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]){
	
	//Crear las variables
	T_LINEA_CACHE linea_cache[NUM_FILAS];
	
	int variable1 = 0xFF;
	int variable2 = 0x23;
	
	//Llamar a las funciones
	VuelcaCACHE(linea_cache);
	
	return 0;
}

//FUNCION CAMBIAR DE HEXADECIMAL A DECIMAL
int cambioHexadecimalADecimal(long long numero ){
	
	//Variables
	int i = 0;
	int variable_auxiliar;
	int numero_devuelto = 0;
	
	while(numero != 0){
		variable_auxiliar = numero % 10;
		numero = numero / 10;
		numero_devuelto = numero_devuelto + (variable_auxiliar * (pow(2, i)));
		++i;
	}
	
	return numero_devuelto;
}

void LimpiaCACHE(T_LINEA_CACHE tbl[NUM_FILAS]){ 
    
    for(int i=0; i<NUM_FILAS; i++){
    	tbl[i].ETQ= 0xFF;
    	for(int j=0; j<TAM_LINEA;j++){
    		tbl[i].Datos[j]= 0x23;
		}
	}
    
}
void VuelcaCACHE(T_LINEA_CACHE *tbl){
	
	for(int i=0;i<NUM_FILAS; i++){
		
		printf("ETQ: %02X  Data ", tbl[i].ETQ);
		for(int j=0; j<TAM_LINEA; j++){
			printf("%02X ", tbl[i].Datos[j]);
		}
		printf("\n");
	}
}
