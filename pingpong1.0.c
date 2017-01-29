#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
  pid_t hijo;
  int leer = 0, escribir = 0;
  int tuberia_padre[1], tuberia_hijo[1];
  char Buffer_padre[100], Buffer_hijo[100], PING[60], PONG[60];

  abrir_tuberia(tuberia_padre);
  abrir_tuberia(tuberia_hijo);

  hijo = fork();

  if (hijo == 0) {
    /* Rama del hijo*/
    cerrar_tuberia(tuberia_hijo, 0);
    cerrar_tuberia(tuberia_padre, 1);

    while (1) {
      leer = read(tuberia_padre[0], Buffer_hijo, sizeof(Buffer_hijo));
      if (leer == -1) {
        perror("Error al leer en el hijo.");
        exit(EXIT_FAILURE);
      }

      sleep(1);

      escribir = write(1, Buffer_hijo, leer);
      if (escribir == -1) {
        perror("Error al escribir en el hijo.");
        exit(EXIT_FAILURE);
      }

      strcpy(PONG, "PONG\n");
      escribir = write(tuberia_hijo[1], PONG, strlen(PONG));
      if (escribir == -1) {
        perror("Error al escribir en el hijo.");
        exit(EXIT_FAILURE);
      }
    }
  }else{
    /*Rama del padre*/
    cerrar_tuberia(tuberia_hijo, 1);
    cerrar_tuberia(tuberia_padre, 0);

    while (1) {

      strcpy(PING, "PING\n");
      escribir = write(tuberia_padre[1], PING, strlen(PING));
      if (escribir == -1) {
        perror("Error al escribir en el padre.");
        exit(EXIT_FAILURE);
      }

      leer = read(tuberia_hijo[0], Buffer_padre, sizeof(Buffer_padre));
      if (leer == -1) {
        perror("Error al leer en el padre.");
        exit(EXIT_FAILURE);
      }

      sleep(1);
      escribir = write(1, Buffer_padre, leer);
      if (escribir == -1) {
        perror("Error al escribir en el hijo.");
        exit(EXIT_FAILURE);
      }
    }
  }
  return 0;
}
