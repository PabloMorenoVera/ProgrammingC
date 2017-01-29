#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int abrir_fichero_lectura(char fichero[]){
  int abrir = 0;

  abrir = open(fichero, O_RDONLY);
  if (abrir == -1) {
    perror("Error al abrir el fichero de lectura.");
    exit(EXIT_FAILURE);
  }
  return abrir;
}

int leer_palabra(int fichero, char  palabra[]) {
  int leer  = 0, i = 0;
  char c;

  while ((c != ' ') && (c != '\n')) {
    leer = read(fichero, &c, sizeof(c));
    if (leer == -1) {
      perror("Error al leer del fichero.");
      exit(EXIT_FAILURE);
    }else if (leer == 0) {
      return 1;
    }
    if ((c != ' ') && (c != '\n')) {
      palabra[i] = c;
    }
    i=i+1;
  }
  return 0;
}

static void abrir_tuberia(int tuberia[]) {
  int abrir = 0;

  abrir = pipe(tuberia);
  if (abrir == -1) {
    perror("Error al abirr las tuberías.");
    exit(EXIT_FAILURE);
  }
}

static void cerrar_tuberia(int tuberia) {
  int cerrar = 0;

  cerrar = close(tuberia);
  if (cerrar == -1) {
    perror("Error al cerrar una tubería.");
    exit(EXIT_FAILURE);
  }
}

static void escribir_tuberia(int tuberia, char palabra[]) {
  int escribir = 0;

  escribir = write(tuberia, palabra, strlen(palabra));
  if (escribir == -1) {
    perror("Error al escrbir.");
    exit(EXIT_FAILURE);
  }
}

static void leer_tuberia(int tuberia, char frase[]) {
  int leer = 0;
  char Buffer[1024] = "";

  leer = read(tuberia, Buffer, sizeof(Buffer));
  if (leer == -1) {
    perror("Error al leer la tubería.");
    exit(EXIT_FAILURE);
  }
  strcpy(frase, Buffer);
}

int main(int argc, char const *argv[]) {
  int fichero = 0, index = 0, tuberia_padre[2], tuberia_hijo[2], status = 0, options = 0;
  char frase[1024] = "", palabra[30] = "";
  pid_t hijo = 0;

  fichero = abrir_fichero_lectura("lectura.txt");
  while (index != 1) {
    memset(palabra, '\0', strlen(palabra));
    index = leer_palabra(fichero, palabra);
    if (index == 1) {
      return 0;
    }else{
      printf("palabra: %s\n", palabra);
    }

    abrir_tuberia(tuberia_padre);
    abrir_tuberia(tuberia_hijo);

    hijo = fork();

    if (hijo == 0) {
      /* Rama del hijo */

      cerrar_tuberia(tuberia_padre[1]);
      cerrar_tuberia(tuberia_hijo[0]);

      leer_tuberia(tuberia_padre[0], frase);
      printf("Leido: %s\n", frase);
      escribir_tuberia(tuberia_hijo[1], "Palabra enviada correctamente.");


      cerrar_tuberia(tuberia_padre[0]);
      cerrar_tuberia(tuberia_hijo[1]);
      exit(0);

    }else{
      /* Rama del padre */

      cerrar_tuberia(tuberia_padre[0]);
      cerrar_tuberia(tuberia_hijo[1]);

      escribir_tuberia(tuberia_padre[1], palabra);

      leer_tuberia(tuberia_hijo[0], frase);

      waitpid(hijo, &status, options);
      if (WIFEXITED(status)) {
        printf("El hijo %d ha terminado correctamente.\n", hijo);
      }else{
        printf("El hijo %d no ha terminado correctamente.\n", hijo);
      }

      cerrar_tuberia(tuberia_padre[1]);
      cerrar_tuberia(tuberia_hijo[0]);
    }
  }

  return 0;
}
