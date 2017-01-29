#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programa para la utilización de los strings en C.

// Un puntero que señala a una dirección de memoria que termine en \0 se considera un string.

int main ()
{

	char *str = "Hola";	// Equivale a crear un puntero que señala a la 'h' y tiene de celdas: 'h' 'o' 'l' 'a' '\0'.
	char *ctr = "Vida";
	
	printf("Tamaño del string: %lu\n", strlen(str));	//strlen(string) nos da el tamañao del string sin el nulo.
								// strnlen(string) se usa para cuando no sabemos si hay un \0 de terminación.
								
	// Otro comando es strcmp(string1, string2) para comparar lexicamente dos palabras. También está strncmp. Si son iguales devuelve 0.
	printf("Palabra preferente léxicamente: ");
	if(strcmp(str, ctr) != 0){
		printf("%c\n", *str);
	}else{
		printf("%c\n", *ctr);
	}
	// Otro comando es strcpy(string1 string2) para copiar un string en otro aunque debemos asegurar que el string nuevo tiene espacio 		suficiente. 
	
	exit(0);
}
