#include <stdlib.h>
#include <stdio.h>

// Un booleano es un entero. Si es igual a "0" es falso y si es distinto de "0" es verdadero.

int main()
{

	int i;
	int j;
	
	i = 5;
	j = 6;
	printf ("\nValor i: %d, Valor j: %d\n", i, j);
	
	printf ("i es menor que j: %d\n", i < j);	//Como esta sentencia es verdad, el valor serà "1" o distinto de "0".
	printf("i es mayor que j: %d\n\n", i > j);	//Como esta sentencia es falsa, el valor serà "0".
	
	i = 7;
	j = 6;
	printf ("Valor i: %d, Valor j: %d\n", i, j);
	
	printf("i es menor que j: %d\n", i < j);	//Como esta sentencia es falsa, el valor serà "0".
	printf("i es mayor que j: %d\n\n", i > j);	//Como esta sentencia es verdad, el valor serà "1" o distinto de "0".

// Operaciones con Booleanos.

	i = 7;
	j = 6;
	
	if(i == 7)
		printf("i es igual a %d\n", i);
	if(j != 7){
		printf("j es distinto de 7,");
		printf(" es igual a %d\n\n", j);
	}
	
// Operaciones de and(&&) y or(||) en un if.

	if(i == 7 && j == 6)
		printf("i es igual a %d, y j es igual a %d\n", i, j);
	if(i == 7 && j != 7)
		printf("i es igual a %d, y j es distinto de 7, es igual a %d\n\n", i, j);	
		
		
	i = 5;
	j = 5;
	printf("Valor de i: %d, Valor de j: %d\n\n", i, j);
	
	if(i != 5 || j == 5)
		printf("i es distinto de 5 o j es igual a %d\n", j);
	if(i != 5 || j != 5 || i == j)
		printf("i es distinto de %d, j es distinto de %d o i es igual a j = %d\n", i, j, i);
	if(i == 5 && 0 && j == 5)
		printf("Esto es falso\n");
	if(i == 5 && 1 && j ==5)
		printf("Esto es cierto, && 1 &&\n");
	if(i == 5 || 0 || j == 5)
		printf("Esto es correcto, || 0 ||, pero i == 5, j == 5\n");
	if(i == 5 || 1 || j ==5)
		printf("Esto es verdadero, || 1 ||\n"); 
			
	printf("\n");	
	exit(0);
}
