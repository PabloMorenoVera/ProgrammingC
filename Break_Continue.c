#include <stdlib.h>
#include <stdio.h>

// Programa para el uso de Break y Continue en los bucles.

int main()
{
	
	int i;
	
	for(i = 0; i < 10; ++i){
		printf("%d ", i);
		if(i == 5)
			break;		//Termina con el bucle.
	}
	printf("\n");
	
	for(i = 0; i < 10; ++i){
		if(i == 5)
			continue;	//Salta esa vuelta del bucle.
		printf("%d ", i);
	}
	
	printf("\n");
	
	exit(0);
}
