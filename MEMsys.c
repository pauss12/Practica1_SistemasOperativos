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

//ESTRUCTURA LINEAS CACHE -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
void leer_fichero_contents_RAM();

bool comparar_etiqueta(int etiqueta, int linea);

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
	leer_fichero_contents_RAM();
	
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

//FUNCION LEER FICHERO CONTENTS RAM ----------------------------------------------------------------------------------------
void leer_fichero_contents_RAM(){
	
	FILE* fichero_bin;
	
	//Abrir el fichero en modo de lectura ("rb", (READ BINARY))
	fichero_bin = fopen("CONTENTS_RAM.bin", "rb");
	
	if(fichero_bin != NULL){
		//Leemos fichero y lo cargamos
		fread(SIMUL_RAM	, sizeof(Simul_RAM), 1, fichero_bin);
	
	}else{
		printf("El archivo no existe!!");
		exit(-1);
	}
}

//FUNCION TRATAR FALLO --------------------------------------------------------------------------------------------------*/
void tratarFallo(CACHE_LINE *tbl, char *MRAM, int ETQ,int linea, int bloque, int * direccion_array){
    numfallos= numfallos + 1;
    globaltime= globaltime + 10;
    
    printf("time: %d, Fallo de CACHE %d, addr %s ETQ %X linea %02X palabra %02X bloque %02X \n", globaltime,numfallos,lineas,direccion_array[0],direccion_array[1],direccion_array[2],direccion_array[3]);

    printf("Cargando el bloque %02X en la linea %02X \n",direccion_array[3],direccion_array[1]);
    CACHE_LINE[direccion_array[1]].ETQ=direccion_array[0];//Cargamos la nueva etiqueta
    
    //Extración del texto
    for(int i=0;i<TAM_LINEA;i++){
        CACHE_LINE[direccion_array[1]].Data[i] = Simul_RAM[direccion_array[3]+TAM_LINEA*i];
    }


//LEER FICHERO ---------------------------------------------------------------------------------------------------------------------------
//Comprueba que el fichero se ha escrito todo bien y como debe de ser.
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

//Comprobar la etiqueta ----------------------------------------------------------------------------------------------------------------

bool comparar_etiqueta(int etiqueta, int linea){
	
	 if((int)cacheLine[linea].ETQ==etiqueta){
        return true;
    }else{
        return false;
    }
}


//ESCRIBIR EN FICHERO ------------------------------------------------------------------------------------------------------
int escritura_en_fichero_binario(){
	
	FILE * fichero2;
    //Buffer con la información para escribir
    char wbuffer[256];
    int cont=0;

    //Abrir fichero modo escritura ("w+b" write binary, en caso de no existir lo crea y si existe lo crea de nuevo)
    fichero2 = fopen("CONTENS_CACHE.bin", "w+b");
    
    if (fichero2==NULL){
        perror("No se puede abrir CONTENS_CACHE.bin");
        return -1;
    }else{
        //Recorremos cacheLine[x].data y extraemos su contenido y lo almacenamos en el buffer 
        for(int i=0;i<16;i++){
            for(int j=0;j<TAM_LINEA;j++){
                wbuffer[cont]=cacheLine[i].Data[j];
                cont++;
            }
        }

        //Escribe el contenido en el archivo
        for (int k = 0; k < 256; k++){
            fwrite(wbuffer, sizeof(wbuffer),1,fichero2);
        }
    }
}

//Lee el fichero accesos_memoria.txt ---------------------------------------------------------------------------------------------------------------------------
int lectura_del_fichero_de_memoria(){
    int n;
    FILE * fichero;
    //abre fichero de lectura
    fichero = fopen("accesos_memoria.txt", "r");
    int direccion_cortada [4];
    int * direccion_array;

    if(fichero != NULL){
        char lineas [5];

        //Metodo para recorrer el fichero y almacenar el contenido en "lineas"
        while(fgets(lineas,sizeof(lineas),fichero)!=NULL){
            globaltime++;
            direccion_array=binarioConversion(direccion_cortada,lineas);
            //Eliminar el buffer
            lineas[strcspn(lineas, "\n")] = 0;
            //comparar las etiquetas para ver si son iguales y si no tratar el fallo
            if(comparar_Etiqueta(direccion_array[0],direccion_array[1])){
                
                printf("tiempo: %d, Acierto %d, addr %s ETQ %X linea %02X palabra %02X dato %02X \n", globaltime,accesostotales-numfallos+1,lineas,direccion_array[0],direccion_array[1],direccion_array[2],CACHE_LINE[direccion_array[1]].Data[direccion_array[2]]);
            }else{
                tratarFallo(direccion_array,lineas);
            }
            //registro de acceso
            texto[accesostotales]=CACHE_LINE[direccion_array[1]].Data[direccion_array[2]];
            accesostotales++;
            sleep(1);
        }

    }else{
        //Caso error
        printf("ERROR EN EL ARCHIVO SELECCIONADO");
        exit(-1);
    }
    return 0;
}