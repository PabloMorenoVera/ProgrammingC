/* Pablo Moreno Vera */
/* Doble Grado IST y ADE */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void Comprobar_error(int Chek) {
  if (Chek == -1) {
    perror("Error.");
    exit(EXIT_FAILURE);
  }
}

char Convertir_simbolo(char op[]){

  if (strcmp(op, "MUL") == 0) {
    return '*';
  }else if (strcmp(op, "DIV") == 0) {
    return '/';
  }else if (strcmp(op, "SUM") == 0) {
    return '+';
  }else if (strcmp(op, "SUB") == 0) {
    return '-';
  }else{
    perror("Error al convertir el símbolo.");
    exit(EXIT_FAILURE);
  }
}

int Leer_linea(int Fichero, char operacion[]){

  int leer = 0;
  char c, op[100] = "";

  leer = read(Fichero, &c, sizeof(c));
  Comprobar_error(leer);

  if (c == '/') {                             /*Leo el comentario*/
    while (c != '\n') {
      leer = read(Fichero, &c, sizeof(c));
      Comprobar_error(leer);
    }
    if (c == '\n') {
      return -2;
    }
  }else if (leer == 0) {
    return -1;
  }
  operacion[0] = c;                           /*Asigno el primer número*/

  leer = read(Fichero, &c, sizeof(c));        /*Leo el espacio*/
  Comprobar_error(leer);

  for (size_t i = 0; i < 3; i++) {
    leer = read(Fichero, &c, sizeof(c));        /*Leo las letras*/
    Comprobar_error(leer);

    op[i] = c;
  }

  operacion[1] = Convertir_simbolo(op);       /* Asigno el símbolo*/

  leer = read(Fichero, &c, sizeof(c));        /*Leo el espacio*/
  Comprobar_error(leer);

  leer = read(Fichero, &c, sizeof(c));        /*Leo el segundo número*/

  Comprobar_error(leer);
  operacion[2] = c;                           /*Asigno el  segundo número*/

  while (c != '\n') {
    leer = read(Fichero, &c, sizeof(c));      /*Leo hasta el final de línea*/
    Comprobar_error(leer);
  }

  operacion[3] = '\n';                        /*Introduzco el fin de línea*/
  return 0;
}

static void abrir_tuberia(int tuberia[2]){
  int abrir = 0;

  abrir = pipe(tuberia);
  Comprobar_error(abrir);
}

static void cerrar_descriptor(int descriptor) {
  int cerrar = 0;

  cerrar = close(descriptor);
  Comprobar_error(cerrar);
}

static void escribir_tuberia(int tuberia, char operacion[]) {
  int escribir = 0;


  escribir = write(tuberia, operacion, strlen(operacion));
  Comprobar_error(escribir);
}

static void leer_operacion(int tuberia, char operacion[]) {
  int leer = 0;

  leer = read(tuberia, operacion, strlen(operacion));
  Comprobar_error(leer);
  write(1, operacion, strlen(operacion));

}

int main(int argc, char const *argv[]) {

  int Fichero_Origen = 0, Fichero_Destino = 0, index = 0, Hijo = 0;
  int tuberia_hijo[2], tuberia_padre[2];
  char operacion[500] = "", Resultado[500] = "";

  if (argc != 3) {
    printf("Número de argumentos inválidos.\n");
    printf("Por favor, introduzca: Fichero_Origen y Fichero_Destino.\n");
    return 0;
  }

  Fichero_Origen = open(argv[1], O_RDONLY);
  Comprobar_error(Fichero_Origen);
  Fichero_Destino = open(argv[2], O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
  Comprobar_error(Fichero_Destino);

  abrir_tuberia(tuberia_padre);                 /*Abro las tuberías*/
  abrir_tuberia(tuberia_hijo);

  Hijo = fork();
  if (Hijo == 0) {
                                                /*Rama del hijo*/
    cerrar_descriptor(tuberia_hijo[0]);
    cerrar_descriptor(tuberia_padre[1]);

//    leer_operacion(tuberia_padre[0], operacion);

    cerrar_descriptor(0);                       /*Hago el dup de lectura*/
    dup(tuberia_padre[0]);
    cerrar_descriptor(tuberia_padre[0]);

    cerrar_descriptor(1);                       /*Hago el dup de escritura*/
    dup(Fichero_Destino);
    cerrar_descriptor(Fichero_Destino);

    execl("/usr/bin/bc", "/usr/bin/bc", NULL);

  }else{
                                                /*Rama del padre*/
    cerrar_descriptor(tuberia_hijo[1]);
    cerrar_descriptor(tuberia_padre[0]);

    while (index != -1) {
      index = Leer_linea(Fichero_Origen, operacion);

      if (index == 0) {
        escribir_tuberia(tuberia_padre[1], operacion);
      }
    }
  }
  printf("Programa terminado.\n");
  return 0;
}
