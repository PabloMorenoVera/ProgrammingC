#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void abrir_tuberia(int tuberia[]) {
  int abrir = 0;

  abrir = pipe(tuberia);
  if (abrir == -1) {
    perror("Error al abrir las tuberías.");
    exit(EXIT_FAILURE);
  }
}

static void cerrar_tuberia(int tuberia[], int i) {
  int cerrar = 0;

  cerrar = close(tuberia[i]);
  if (cerrar == -1) {
    perror("Error al cerrar la tubería.");
    exit(EXIT_FAILURE);
  }
}

int abrir_fichero(char fichero[]){
  int abrir = 0;

  abrir = open(fichero, O_RDONLY);
  if (abrir == -1) {
    perror("Error al abrir el archivo de lectura.");
    exit(EXIT_FAILURE);
  }
  return abrir;
}

int leer_fichero(int fichero, char linea[]) {
  int leer = 0, i = 0;
  char c;

  while (c != '\n') {
    leer = read(fichero, &c, sizeof(c));
    if (leer == -1) {
      perror("Error al leer el fichero");
      exit(EXIT_FAILURE);
    }
    linea[i] = c;
    ++i;
  }
  return i;
}

int main(int argc, char const *argv[]) {
  pid_t hijo = 0;
  int fichero = 0, tuberia, index = 0;
  int tuberia_padre[2], tuberia_hijo[2];
  char linea[1024] = "";

  abrir_tuberia(tuberia_padre);
  abrir_tuberia(tuberia_hijo);

  hijo = fork();

  if (hijo == 0) {
    cerrar_tuberia(tuberia_hijo, 0);
    cerrar_tuberia(tuberia_padre, 1);
  }else{
    cerrar_tuberia(tuberia_padre, 0);
    cerrar_tuberia(tuberia_hijo, 1);

    fichero = abrir_fichero("lectura.txt");

    index = leer_fichero(fichero, linea);
    printf("%s\n", linea);
    printf("%d\n", index);
    index = leer_fichero(fichero, linea);
    printf("%s\n", linea);
    printf("%d\n", index);
    index = leer_fichero(fichero, linea);
    printf("%s\n", linea);
    printf("%d\n", index);
    index = leer_fichero(fichero, linea);
    printf("%s\n", linea);
    printf("%d\n", index);
  }

  return 0;
}
