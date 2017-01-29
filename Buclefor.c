#include <stdio.h>
#include <stdlib.h>

//Uso del bucle "for". En el bucle "for" se utilizan "idioms", bucles for predeterminados. Solo se crea un bucle for si 
// requiere algun uso concreto del que no existe un idiom.

int main()
{

	int i;
	
	for(i = 0; i < 10; i++){
		printf("Te quiero\n");
	}
	
//	for(;;;){
//		printf(".");		Esto es un bucle infinito
//	}
	
//	for(i = 0;; i++){
//		printf(".");		Esto es un bucle infinito pues no hay sentencia de control.
//	}

	for(i = 0; 0; i++){
		printf("Hola fea");	//Como la sentencia de control es false: "0", no se ejecuta el bucle.
	}
	
	
// Idioms de bucle for.

//	int i;
	
	for(i = 9; i >= 0; --i){
		printf("%d\n", i);	//Bucle para contar de "n" hasta "0"
	}	
	
	exit(0);
}
