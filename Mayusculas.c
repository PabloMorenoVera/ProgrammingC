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

static void leer_fichero(int fichero, char texto[]) {
  int leer = 0;
  char buffer[1024] = "";

    leer = read(fichero, buffer, sizeof(buffer));
    if (leer == -1) {
      perror("Error al leer el fichero");
      exit(EXIT_FAILURE);
    }
    strcpy(texto, buffer);
}

int trocear_texto(char texto[], char frase[], int index) {
  int i = 0;
  
  while (texto[index] != '\n') {
    frase[i] = texto[index];
    ++i; ++index;
  }
  return index;
}


int main(int argc, char const *argv[]) {
  pid_t hijo = 0;
  int fichero = 0, tuberia, index = 0, longitud = 0;
  int tuberia_padre[2], tuberia_hijo[2];
  char texto[1024] = "", linea[150] = "";

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

    leer_fichero(fichero, texto);
    longitud = strlen(texto);


    index = trocear_texto(texto, linea, index);
    printf("%s\n", linea);

    while (index < longitud) {
      memset(linea, '\0', strlen(linea));
      index = trocear_texto(texto, linea, index+1);
      printf("%s\n", linea);
    }

  }



  return 0;
}
