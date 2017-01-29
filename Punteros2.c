#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programa sobre el uso de punteros II.

int main ()
{
	char cp[10];
	int *ip;
	
	ip = (int *)cp;
	*ip = 28;
	
//	void *z; Puntero creado pero que no se puede aplicar aritmética de punteros puesto que no está inicializado. Sirve para guardar una 			dirección de memoria.
			
	int *x;
	
	x = malloc(10+sizeof(int));	// Reservo memoria para 10 enteros.
	x[3] = 10;			// Guardo un 10 en la posición 4 del array.
	free (x);			// Libero memoria que se ha reservado con malloc. Tengo que pasarle un puntero creado con malloc.
	
// Para poner a cero regiones de memoria se utiliza la función memset.
// Para copiar memoria en crudo se utliza memmove(*dest, *src, num_Bytes), copia el numero de bytes de la fuente al destino.

	struct Point{
		int x;
		int y;
	};
	typedef struct Point Point;
	
	Point p, q;
	
	memset(&p, 0, sizeof(p));
	p.x = 5;
	memmove(&q, &p, sizeof(p));
	
	printf("p.x: %d, q.x: %d\n", p.x, q.x);
	
// Para declarar un puntero a funcion en C.	typedef int (*cmpf)(int a, int b);

	exit(0);
}
