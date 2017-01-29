#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void asignar_simbolo(char operacion[], char op[]) {

  if (strcmp (op , "MUL")) {
    operacion[1] = '*';
  }else if (strcmp (op , "SUM")) {
    operacion[1] = '+';
  }else if (strcmp (op , "DIV")) {
    operacion[1] = '/';
  }else if (strcmp (op , "SUB")) {
    operacion[1] = '-';
  }else{
    perror("Error al asginar la operacion.");
    exit(EXIT_FAILURE);
  }
}

int leer_linea(int Fichero, char operacion[]){
  int leer = 0, i = 0;
  char c, op[3] = "";

  leer = read(Fichero, &c, sizeof(c));
  if (leer == -1) {
    perror("Error al leer del fichero.");
    exit(EXIT_FAILURE);
  }else if (leer == 0) {
    return -1;
  }else if (c == '/') {
    while (c != '\n') {
      leer = read(Fichero, &c, sizeof(c));
      if (leer == -1) {
        perror("Error al leer del fichero.");
        exit(EXIT_FAILURE);
      }
    }
  }else{
    operacion[0] = c;

    leer = read(Fichero, &c, sizeof(c)); /*Leo el espacio*/
    if (leer == -1) {
      perror("Error al leer del fichero.");
      exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < 3; i++) {
      leer = read(Fichero, &c, sizeof(c));
      if (leer == -1) {
        perror("Error al leer del fichero.");
        exit(EXIT_FAILURE);
      }
      op[i] = c;
    }

    asignar_simbolo(operacion, op);

    leer = read(Fichero, &c, sizeof(c)); /*Leo el espacio*/
    if (leer == -1) {
      perror("Error al leer del fichero.");
      exit(EXIT_FAILURE);
    }

    leer = read(Fichero, &c, sizeof(c));
    if (leer == -1) {
      perror("Error al leer del fichero.");
      exit(EXIT_FAILURE);
    }

    operacion[2] = c;
    return 0;
  }

}

static void abrir_tuberia(int tuberia[]) {
  int abrir = 0;

  abrir = pipe(tuberia);
  if (abrir == -1) {
    perror("Error al abrir la tubería.");
    exit(EXIT_FAILURE);
  }
}

static void cerrar_descriptor(int descriptor) {
  int cerrar = 0;

  cerrar = close(descriptor);
  if (cerrar == -1) {
    perror("Error al cerrar el descriptor.");
    exit(EXIT_FAILURE);
  }
}

static void escribir_operacion(int tuberia, char operacion[]) {
  int escribir = 0;

    escribir = write(tuberia, &operacion, strlen(operacion));
    if (escribir == -1) {
      perror("Error al escribir la operación.");
      exit(EXIT_FAILURE);
    }
}

int main(int argc, char const *argv[]) {
  int Fichero = 0, index = 0,  tuberia_padre[2], tuberia_hijo[2];
  int Fichero_Destino = 0;
  char operacion[10] = "";
  pid_t hijo = 0;

  if (argc != 3) {
    printf("Número de argumentos incorrecto.");
    printf("Por favor, introduzca: Fichero_Origen y Fichero_Destino.\n");
  }

  Fichero = open(argv[1], O_RDONLY);
  if (Fichero == -1) {
    perror("Error al abrir el fichero de lectura.");
    exit(EXIT_FAILURE);
  }

  index = leer_linea(Fichero, operacion);

  abrir_tuberia(tuberia_padre);
  abrir_tuberia(tuberia_hijo);

  hijo = fork();

  if (hijo == 0) {
    /* code */

    cerrar_descriptor(tuberia_hijo[0]);
    cerrar_descriptor(tuberia_padre[1]);

    cerrar_descriptor(0);
    dup(tuberia_padre[0]);
    cerrar_descriptor(tuberia_padre[0]);

    cerrar_descriptor(1);
    Fichero_Destino = open(argv[2], O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    if (Fichero_Destino == -1) {
      perror("Error al abrir el fichero de lectura.");
      exit(EXIT_FAILURE);
    }
    dup(Fichero_Destino);
    cerrar_descriptor(Fichero_Destino);

    execl("/usr/bin/bc", "/usr/bin/bc", NULL);

  }else{

    cerrar_descriptor(tuberia_hijo[1]);
    cerrar_descriptor(tuberia_padre[0]);

    escribir_operacion(tuberia_padre[1], operacion);

  }

  return 0;
}
