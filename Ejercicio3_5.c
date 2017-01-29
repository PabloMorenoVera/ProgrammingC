#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void abrir_tuberia(int tuberia[]){
  int abrir = 0;

    abrir = pipe(tuberia);
    if (abrir == -1) {
      perror("Error al abrir tuberia.");
      exit(EXIT_FAILURE);
    }
}

void cerrar_tuberia(int tuberia[], int a) {
  int cerrar = 0;

  cerrar = close(tuberia[a]);
  if (cerrar == -1) {
    perror("Error al cerrar la tuberia.");
    exit(EXIT_FAILURE);
  }

}

int main(int argc, char const *argv[]) {
  int a = 0, b = 0, Resultado = 0, Resultado1 = 0;
  int Buffer_padre[1024], Buffer_hijo[1024];
  pid_t hijo = 0;
  int tuberia_padre[2], tuberia_hijo[2];
  int leer = 0, escribir = 0;

  abrir_tuberia(tuberia_padre);

  abrir_tuberia(tuberia_hijo);

  hijo = fork();
  if (hijo == -1) {
    perror("Error al crear el hijo");
    exit(EXIT_FAILURE);
  }

  if (hijo == 0) {
    /*Código del hijo*/
    cerrar_tuberia(tuberia_hijo, 0);

    for (size_t i = 0; i < 2; i++) {
      leer = read(tuberia_padre[0], Buffer_hijo, sizeof(Buffer_hijo));
      if (leer == -1) {
        perror("Error al leer del padre.");
        exit(EXIT_FAILURE);
      }
      a = Buffer_hijo[0];
      b = Buffer_hijo[1];

      Resultado = a + b;

      Buffer_hijo[0] = Resultado;
      escribir = write(tuberia_hijo[1], Buffer_hijo, sizeof(Buffer_hijo));
      if (escribir == -1) {
        perror("Error al escribir en el hijo.");
        exit(EXIT_FAILURE);
      }
    }
    cerrar_tuberia(tuberia_hijo, 1);
    cerrar_tuberia(tuberia_padre, 0);

  }else{
    /*Código del padre*/
    cerrar_tuberia(tuberia_padre, 0);

    for (size_t i = 0; i < 2; i++) {
      printf("Escribe un número: ");
      scanf("%d", &a);
      printf("Escribe otro número: ");
      scanf("%d", &b);

      Buffer_padre[0] = a;
      Buffer_padre[1] = b;

      escribir = write(tuberia_padre[1], Buffer_padre, sizeof(Buffer_padre));
      if (escribir == -1) {
        perror("Error al escribir en el padre.");
        exit(EXIT_FAILURE);
      }

      leer = read(tuberia_hijo[0], Buffer_padre, sizeof(Buffer_padre));
      if (leer == -1) {
        perror("Error al leer del hijo.");
        exit(EXIT_FAILURE);
      }

      Resultado1 = Buffer_padre[0];
      printf("El resultado es: %d\n", Resultado1);
    }

    cerrar_tuberia(tuberia_padre, 1);
    cerrar_tuberia(tuberia_hijo, 0);
  }

  return 0;
}
