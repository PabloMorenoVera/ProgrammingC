#include <stdio.h>
#include <stdlib.h> 

int main ()
{
	char i; //Aunque cambiásemos la variable por un char, el programa no daría error puesto que asigna un espacio de memoria, no un tipo.
	i = 'a';
	
	printf("\nEscribe el numero ASCII guardado en la variable i: %d\n", i); //Para ver el código ASCII usamos %d.
	printf("Escribe la letra guardada en la variable i: %c\n\n", i); //Para ver el char usamos %c.
	
// Vamos a ver el tamaño que ocupa.

	int j;

	printf("Tamaño de j(int): %lu\n", sizeof j);	//Expresion %lu porque no sabemos cuánto ocupa nuestra variable. Saltaría error.
	printf("Tamaño (bytes) de un char: %lu\n\n", sizeof(char));	
	
// Importancia del signo en enteros.

	printf("\n Desbordamiento.\n ----------------- \n\n");

	char k;
	k = 255;
	
	printf("Valor de k(Con signo[255]): %d\n", k); //Da el valor -1 puesto que es el valor de 255 en Complemento a2.
	
	unsigned char l;
	l = 255;		//Si asignasemos el valor mayor a 256 saldría un warning y valor empezaría a partir de 0.
	
	printf("Valor de l(Sin signo[255]): %d\n", l);
	
	unsigned char g;
	g = -1;
	
	printf("Valor de g(Sin signo[-1]): %d\n", g);
	
	char h;
	h = 255;
	
	printf("Valor de f(Con signo[-1]: %d\n", h);
	
// Comparación número con signo y sin signo
	
	unsigned char p;
	signed char v;
	
	p = -1;
	v = -1;
	
	if (p > v){	
		printf("%d > %d \n", p, v);
	}else{
		printf("%d > %d \n", v, p);
	}
	
	exit(0);
	
}
