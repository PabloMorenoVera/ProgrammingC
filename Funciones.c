#include <stdlib.h>
#include <stdio.h>

// Programa para la práctica de funciones en C.
// Si en una función no se devuelve nada se escribe: void "nombre_de_la_función (argumentos)".
// Si a una función no se le pasan argumentos se escribe: "nombre_de_la_función (void)".

int sum (int a, int b)
{
	return a + b;
}

int main ()
{

	int x, y;
	

	printf("X: ");
	scanf("%d", &x);
	printf("Y: ");
	scanf("%d", &y);
	
	printf("La suma de X e Y es: %d\n", sum(x,y));
	exit(0);
}
