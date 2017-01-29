#include <stdio.h>
#include <stdlib.h>

// Programa para la utilización de punteros.

// El símbolo * obtiene el contiene y lo modifica.
// El símbolo & obtiene la dirección.

int main ()
{

	int i;
	int *ip;	// Es un puntero porque lleva "*".
	
	i = 3;
	ip = &i;	// Consigue la dirección en la que se encuentra la variable i y se la asigna al puntero ip.
	
	printf("El valor de i es: %d\n", *ip);	// Imprimirá 3.
	
	*ip = 4;	// Estamos cambiando el valor de la variable a la que apunta ip, en este i por el valor 4.
	
	printf("El valor de i es: %d\n", i);	// Imprimirá 4.
	
	
	
	int *jp;
	
	i = 15;
	ip = &i;
	jp = ip;
	
	*ip = 9;
	printf("El valor de jp es: %d\n", *jp);	// El valor de jp será 9 dado que la sentencia de antes ha cambiado el valor de i a 9.
	
	
	char *cp;
	char c;
	int *kp;
	int k;
		
	c = 'a';
	k = 10;	
	cp = &c;
	kp = &k;
	
	printf("Direccion cp: %p, Dirección kp: %p\n", cp, kp);
	cp = cp + 5;	// Como el tamaño de un char es 1 byte, muevo la posición a la que apunta cp 5 bytes.
	kp = kp + 2;	// Como el tamaño de un entero son 4 bytes, muevo la dirección a la que apunta kp 8 bytes. 
	printf("Direccion cp(+5): %p, Dirección kp(+2): %p\n", cp, kp);
	
// Si sumo un entero y un puntero obtengo un puntero desplazado n veces el sizeoff de a lo que apunto.
// Si resto dos punteros obtengo un entero de valor la diferencia entre las dos direcciones de los punteros.

// Error grave: hacer un return de una función con una variable local.

// Error grave: Imprimir un puntero despues de haberlo desplazado .
// Ejemplo:
//	printf("Valor de cp tras la suma: %d\n", *cp);	ME PUEDE DAR CUALQUIER VALOR PORQUE NO SÉ LO QUE HAY GUARDADO.


// La expresión a[c] indica: a + c.
// La expresión f->y indica que f es un record y estamos acccediendo a su campo y: f.y



	exit(0);
}
