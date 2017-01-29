#include <stdio.h>
#include <stdlib.h>



int main()
{

	int arr[10];
	int arry[] = {1, 2, 3};		// Nos dice la longitud del array
	int array[4] = {0, 1, 2, 3};	// Nos da la longitud del array y lo inicializa.
	
	int i;
	
	for(i = 0; i < 10; i++){
		arr[i] = 10;		// Como hemos visto el uso de corchetes esto es igual que:
	}				// arr(0)+ 3*sizeof(int). Es decir un array es un puntero que siempre señala a la misma zona.
	
	printf("Tamaño de array de 10 posiciones (en bytes): %lu\n", sizeof(arr));
	for(i = 0; i < 10; i++){
		if(i == 9){
			printf("%d\n", arr[i]);
		}else{
			printf("%d ", arr[i]);
		}
	}
	
	printf("Valores de array: %d %d %d %d\n", array[0], array[1], array[2], array[3]);
	
// Como hemos dicho que el array es tipo de puntero se puede utilizar expresiones como:

	int *ip;
	
//	ip = &arr;
	ip = arr;	//Ambos son equivalentes puesto que le da la dirección de la primera celda del array
	printf("Dirección en la que comienza el array: %p\n", ip);

	exit(0);
}
