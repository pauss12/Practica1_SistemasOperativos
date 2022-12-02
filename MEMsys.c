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
//void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);

void parsearDireccion(char binario [],int direccion_cortada []);

//void TrataFallo(T_LINEA_CACHE *tbl, char *MRAM, int ETQ,int linea, int bloque, int * direccion_array);

void tratarFallo(int * arraydireccion,char lineas []);

int cambioHexadecimalADecimal(long long numero );
int *binarioConversion(int *Dir_acortada, char linea []);

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
		fread(Simul_RAM, sizeof(Simul_RAM), 1, fichero_bin);
	}else{
		printf("El archivo no ha sido posible de abrirse!!");
		exit(-1);
	}
}

//FUNCION TRATAR FALLO --------------------------------------------------------------------------------------------------*/
/*
void TrataFallo(T_LINEA_CACHE *tbl, char *MRAM, int ETQ,int linea, int bloque, int * direccion_array){
    numfallos= numfallos + 1;
    globaltime= globaltime + 10;
    
    printf("time: %d, Fallo de CACHE %d, addr %04X Label %X linea %02X palabra %02X DATO %02X \n", globaltime,numfallos, linea,direccion_array[0],direccion_array[1],direccion_array[2],direccion_array[3]);

    printf("Cargando el bloque %02X en la linea %02X \n",direccion_array[3],direccion_array[1]);
	//Cargamos la nueva etiqueta
    linea_cache[direccion_array[1]].ETQ=direccion_array[0];
    
    //Extración del texto
    for(int i=0;i<TAM_LINEA;i++){
        linea_cache[direccion_array[1]].Datos[i] = Simul_RAM[direccion_array[3]+TAM_LINEA*i];
    }

*/

void tratarFallo(int * arraydireccion,char lineas []){
    numfallos+=1;
    globaltime+=10;
    
    printf("T: %d, Fallo de CACHE %d, ADDR %s Label %X linea %02X palabra %02X bloque %02X \n", globaltime,numfallos,lineas,arraydireccion[0],arraydireccion[1],arraydireccion[2],arraydireccion[3]);

    printf("Cargando el bloque %02X en la linea %02X \n",arraydireccion[3],arraydireccion[1]);
    linea_cache[arraydireccion[1]].ETQ=arraydireccion[0];//Cargamos la nueva etiqueta
    
    //Extración del texto
    for(int i=0;i<TAM_LINEA;i++){
        linea_cache[arraydireccion[1]].Datos[i] = Simul_RAM[arraydireccion[3]+TAM_LINEA*i];
    }
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
	
	 if((int)linea_cache[linea].ETQ==etiqueta){
        return true;
    }else{
        return false;
    }
}

// FUNCION CONVERSION A BINARIO

int *binarioConversion(int *Dir_acortada, char linea []){
    char num_binario[100];
	int palabra;
    num_binario[0]='\0'; //poner el string a 0 y borrar lo que tenia dentro

    for (int i = 0; i < 3; ++i){   
        if(isdigit(linea[i])){
            switch(linea[i]){
                case '0' :       
                    strcat(num_binario,"0000");
                    break;
                case '1' :
                    strcat(num_binario, "0001");
                    break;
                case '2' :
                    strcat(num_binario, "0010");
                    break;
                case '3' :
                    strcat(num_binario, "0011");
                    break;
                case '4' :
                    strcat(num_binario, "0100");
                    break;
                case '5' :
                    strcat(num_binario, "0101");
                    break;
                case '6' :
                    strcat(num_binario, "0110");
                    break;
                case '7' :
                    strcat(num_binario, "0111");
                    break;
                case '8' :
                    strcat(num_binario, "1000");
                    break;
                case '9' :
                    strcat(num_binario, "1001");
                    break;
                default : printf("\n el valor no entra en los rangos  %c",linea[i]);
		    }
        }else{
            switch(linea[i]){
                case 'A' :
                    strcat(num_binario, "1010");
                    break;
                case 'B' :
                    strcat(num_binario, "1011");
                    break;
                case 'C' :
                    strcat(num_binario, "1100");
                    break;
                case 'D' :
                    strcat(num_binario, "1101");
                    break;
                case 'E' :
                    strcat(num_binario, "1110");
                    break;
                case 'F' :
                    strcat(num_binario, "1111");
                    break;
                default : printf("\n el valor no entra en los rangos %c",linea[i]);
		    }
        }              
    }

    // ahora toca parsear la direccion
   // ParsearDireccion((int)Dir_acortada, &ETQ, &palabra, &linea, &bloque);

	parsearDireccion(num_binario,Dir_acortada);
	
    return Dir_acortada;
}
//void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque)
//PARSEAR LAS DIRECCIONES --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque){
	*ETQ=addr >> 7;
	*linea=(addr & 0b1110000) >> 4;
	*palabra = addr & 0b1111;
	*bloque = addr >> 4;
}
*/

void parsearDireccion(char num_binario [],int Dir_acortada []){

  char etiqueta[50];
    memcpy(etiqueta,&num_binario[0],5);
    int etiq = atoi(etiqueta);
    Dir_acortada[0]=cambioHexadecimalADecimal(etiq);

    char lineaaa[50];
    memcpy(lineaaa,&num_binario[5],3);
    int linea2 = atoi(lineaaa);
    Dir_acortada[1]=cambioHexadecimalADecimal(linea2);

    char palabra[50];
    memcpy(palabra,&num_binario[8],4);
    int palabra2 = atoi(palabra);
    Dir_acortada[2]=cambioHexadecimalADecimal(palabra2);
   
    char bloque[150];
    memcpy(bloque,&num_binario[0],8);
    int bloque2 = atoi(bloque);
    Dir_acortada[3]=cambioHexadecimalADecimal(bloque2);
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
                wbuffer[cont]=linea_cache[i].Datos[j];
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
  
    FILE * fichero;
    //abre fichero de lectura
    fichero = fopen("accesos_memoria.txt", "r");
    int direccion_cortada [4];
    int * direccion_array;

    if(fichero != NULL){
        char linea [5];

        //Metodo para recorrer el fichero y almacenar el contenido en "lineas"
        while(fgets(linea,sizeof(linea),fichero)!=NULL){
            globaltime++;
            direccion_array=binarioConversion(direccion_cortada,linea);
            //Eliminar el buffer
            linea[strcspn(linea, "\n")] = 0;
            //comparar las etiquetas para ver si son iguales y si no tratar el fallo
            if(comparar_etiqueta(direccion_array[0],direccion_array[1])){
                
                printf("tiempo: %d, Acierto %d, addr %s ETQ %X linea %02X palabra %02X dato %02X \n", globaltime,numeroAccesosTotales-numfallos+1,linea,direccion_array[0],direccion_array[1],direccion_array[2],linea_cache[direccion_array[1]].Datos[direccion_array[2]]);
            }else{
				//TrataFallo(T_LINEA_CACHE *tbl, char *MRAM, int ETQ,int linea, int bloque, int * direccion_array)
                //(LA QUE ESTABA ANTES) TrataFallo(direccion_array,linea,Simul_RAM, label,bloque);
				//TrataFallo(&tbl,&MRAM,ETQ,linea,bloque,direccion_array);
				tratarFallo(direccion_array,linea);
            }
            //registro de acceso
            fichero_texto[numeroAccesosTotales]=linea_cache[direccion_array[1]].Datos[direccion_array[2]];
            numeroAccesosTotales++;
            sleep(1);
        }

    }else{
        //Caso error
        printf("ERROR EN EL ARCHIVO SELECCIONADO");
        exit(-1);
    }
    return 0;
}
