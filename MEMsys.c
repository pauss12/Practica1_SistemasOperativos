//INCLUIMOS TODAS LAS LIBRERIAS QUE NECESITEMOS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

//CREAMOS LOS DEFINE -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define NUM_FILAS 8
#define MAX_LINEA 100
#define TAM_LINEA 8
#define LRAM 1024

//ESTRUCTURA ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	
	unsigned short int ETQ;
	char Datos[TAM_LINEA];
	
}T_LINEA_CACHE;

//PROTOTIPOS DE LAS FUNCIONES -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void LimpiaCACHE(T_LINEA_CACHE tbl[NUM_FILAS]);
void VuelcaCACHE(T_LINEA_CACHE *tbl);
void Parseaaddr(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TrataFallo(T_LINEA_CACHE *tbl, char *MRAM, int ETQ, int linea, int bloque);
int cambioHexadecimalADecimal(long long numero );

int escritura_en_fichero_binario();
void leerBinario();
int lectura_del_fichero_de_memoria();
void leer_fichero();

//VARIABLES GLOBALES -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int globaltime = 0;
	int numfallos = 0;
	unsigned char Simul_RAM[4096];
	T_LINEA_CACHE linea_cache[NUM_FILAS];
	int numeroAccesosTotales = 0;
	char fichero_texto[100];

//MAIN ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]){
	
	//LLAMAR A LAS FUNCIONES
	
	//limpiamos la cache
	LimpiaCACHE(linea_cache);
	
	//Leemos el fichero Binario
	leer_fichero();
	
	//Lectura fichero de memoria
	lectura_del_fichero_de_memoria();
	
	//Mostrar la tabla
	VuelcaCACHE(linea_cache);
	
	printf("\n");
	
	//Mostrar los resultados
	printf("Accesos totales: %d; Fallos: %d; Tiempo medio: %f ", numeroAccesosTotales, numfallos, (double)clock()/1000);
	
	printf("\n");
	
	//Muestra el texto
	printf("Texto leido: %s",fichero_texto);
    printf("\n");
	
    //Escribimos archvo binario
    escritura_en_fichero_binario();
	
	return 0;
}

//FUNCION CAMBIAR DE HEXADECIMAL A DECIMAL --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

//FUNCION LIMPIAR CACHE ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void LimpiaCACHE(T_LINEA_CACHE tbl[NUM_FILAS]){ 
    
    for(int i=0; i<NUM_FILAS; i++){
    	tbl[i].ETQ= 0xFF;
    	for(int j=0; j<TAM_LINEA;j++){
    		tbl[i].Datos[j]= 0x23;
		}
	}
    
}

//FUNCION VOLCAR CACHE ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void VuelcaCACHE(T_LINEA_CACHE *tbl){
	
	for(int i=0;i<NUM_FILAS; i++){
		
		printf("ETQ: %02X  Data ", tbl[i].ETQ);
		for(int j=0; j<TAM_LINEA; j++){
			printf("%02X ", tbl[i].Datos[j]);
		}
		printf("\n");
	}
}

//LEER FICHERO ---------------------------------------------------------------------------------------------------------------------------
void leerBinario(){
	
	FILE * fichero;
    char buffer[256];

    fichero = fopen ("CONTENS_CACHE.bin", "rb");

    if(fichero != NULL){

        fread(buffer,sizeof(buffer),1,fichero);

        for(int i = 0; i<256; i++){
            printf("%c",buffer[i]);// prints a series of bytes %u para numeros
        }

    }else{
        printf("El archivo seleccionado NO EXISTE\n");
        exit(-1);
    }
}

//ESCRIBIR EN FICHERO
int escritura_en_fichero_binario(){
	
	
}