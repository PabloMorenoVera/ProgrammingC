#include <stdlib.h>
#include <stdio.h>

int main ()
{
	int i;
	int j;
	
	i = 10;
	j = 3;
	
	printf("\nEl valor de i es: %d y de j es: %d\n", i, j);
	printf("\n");
	
// Vamos a utilizar operaciones con enteros.
	
	i +=2;
	j *=2;	
	
	printf("El valor de i: %d y el valor de j: %d el valor de i/j: %d\n", i, j, i/j); //Con %d solo cogemos el valor entero.
	printf("\n");
	
// Vamos a utilizar el postincremento y preincremento.

	i =10;
	printf("Postincremento de i: %d\n", i++);	//Como es un post.. el valor de i aumento despues del printf.
	printf("i tras el postincremento: %d\n", i);	//Como vemos tras el printf se incrementa i.
	
	printf("Preincremento de i: %d\n", ++i);	//Como es un pre.. ya esta i incrementado.
	printf("i tras el preincremento: %d\n", i);	//Como vemos el valor de i es el mismo que antes.
	printf("\n");
	
// Vamos a utilizar la predisminucion y la postdisminucion.

	printf("Predisminucion de i: %d\n", --i);
	printf("Postdisminucion de i: %d\n", i--);
	printf("i tras la posdisminucion: %d\n\n", i);
	exit(0);
}
