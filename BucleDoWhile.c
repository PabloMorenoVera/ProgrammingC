#include <stdio.h>
#include <stdlib.h>

//Programa sobre el bucle Do While.

int main ()
{

	int i;

	do{
		printf("Te quiero\n");
		++i;
	}while(i <= 10);
	
	i = 0;
	
	do{
		printf("Te quiero\n");
		++i;
	}while(i%7 != 0);		// Esta sentencia indica que parará cuando el número sea múltiplo de 7.


	exit(0);
}
