#include <stdio.h>
#include <stdlib.h>

// Programa para la utilización de estructuras de datos.

struct point{
	int x;
	int y;
};

// Se pueden renombrar los tipos de datos usando el comando: typedef struct point Point.
// A partir de ahí ya no es necesario poner struct point sino solo Point.

void reg (struct point p)
{
	p.x = 200;
	p.y = 100;
	printf("En la función, P.X vale %d y P.Y vale %d\n", p.x, p.y);
}

int main()
{
	
	struct point p;
//	p.x = 4;
//	p.y = 3;
	
	printf("X: ");
	scanf("%d", &p.x);
	printf("Y: ");
	scanf("%d", &p.y);
	
	reg(p);
	printf("En el programa ppal, el valor de P.X es: %d y el valor de P.Y es %d\n", p.x , p.y);
	
	exit(0);
}
