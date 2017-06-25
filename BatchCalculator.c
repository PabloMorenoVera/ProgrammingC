//Pablo Moreno Vera
// Doble Grado IST y ADE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static void Comprobar_Error(int Chek, char error[]){

  if (Chek == -1) {
    perror(error);
    exit(EXIT_FAILURE);
  }
}

char Convertir_Simbolo(char op[]){

  if (strcmp(op, "SUM") == 0) {
    return '+';
  }else if (strcmp(op, "SUB") == 0) {
    return '-';
  }else if (strcmp(op, "DIV") == 0) {
    return '/';
  }else if (strcmp(op, "MUL") == 0) {
    return '*';
  }else{
    perror("Error al convertir el símbolo");
    exit(EXIT_FAILURE);
  }
}

int Leer_Operacion(int Fichero_O, int Fichero_D, char operacion[]){

  int leer = -1, escribir = -1, i = 1;
  char c, op[5] = "";

  leer = read(Fichero_O, &c, sizeof(c));
  Comprobar_Error(leer, "Error al leer del Fichero_Origen");

  if (leer == 0) {
    return 0;
  }

  if (c == '/') {
    while (c != '\n') {
      leer = read(Fichero_O, &c, sizeof(c));
      Comprobar_Error(leer, "Error al leer del Fichero_Origen");
    }
    return -1;
  }else if (c == '\n') {
    return -1;
  }else{
    operacion[0] = c;

    while (operacion[i-1] != ' ') {
      leer = read(Fichero_O, &operacion[i], sizeof(c));
      Comprobar_Error(leer, "Error al leer del Fichero_Origen");
      ++i;
    }

    for (size_t j = 0; j < 3; j++) {
      leer = read(Fichero_O, &op[j], sizeof(c));
      Comprobar_Error(leer, "Error al leer la operación del Fichero_Origen");
    }

    operacion[i] = Convertir_Simbolo(op);
    ++i;
    leer = read(Fichero_O, &operacion[i], sizeof(c));
    Comprobar_Error(leer, "Error al leer del Fichero_Origen");

    while (operacion[i] != '\n' && operacion[i] != '/') {
      ++i;
      leer = read(Fichero_O, &operacion[i], sizeof(c));
      Comprobar_Error(leer, "Error al leer del Fichero_Origen");
    }

    if (operacion[i] == '/') {
      operacion[i] = '\n';

      while (c != '\n') {
        leer = read(Fichero_O, &c, sizeof(c));
        Comprobar_Error(leer, "Error al leer del Fichero_Origen");
      }
    }

    escribir = write(Fichero_D, operacion, strlen(operacion)-1);
    Comprobar_Error(escribir, "Error al escribir la operación en el Fichero_Destino");

    escribir = write(Fichero_D, " = ", 3);
    Comprobar_Error(escribir, "Error al escribir la operación en el Fichero_Destino");
  }

  return 1;
}

int main(int argc, char const *argv[]) {
  int Fichero_Origen = -1, Fichero_Destino = -1, Hijo = -1;
  int Tuberia_P2H[2], Tuberia_H2P[2];
  int abrir = -1, cerrar = -1, index = -1, leer = -1, escribir = -1;
  char operacion[50] = "";

  if (argc != 3) {
    perror("Error de argumentos, introduce: Fichero_Origen Fichero_Destino");
    exit(EXIT_FAILURE);
  }

  Fichero_Origen = open(argv[1], O_RDONLY);
  Comprobar_Error(Fichero_Origen, "Error al abrir el Fichero_Origen.");

  Fichero_Destino = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  Comprobar_Error(Fichero_Destino, "Error al abrir el Fichero_Destino.");

  abrir = pipe(Tuberia_P2H);
  Comprobar_Error(abrir, "Error al abrir la Tuberia_P2H");

  abrir = pipe(Tuberia_H2P);
  Comprobar_Error(abrir, "Error al abrir la Tuberia_H2P");

  Hijo = fork();
  if (Hijo == 0) {

    cerrar = close(Tuberia_P2H[1]);
    Comprobar_Error(cerrar, "Error al cerrar la Tuberia_P2H[1].");
    cerrar = close(Tuberia_H2P[0]);
    Comprobar_Error(cerrar, "Error al cerrar la Tuberia_H2P[0].");

    cerrar = close(0);
    dup(Tuberia_P2H[0]);
    cerrar = close(Tuberia_P2H[0]);

    cerrar = close(1);
    dup(Fichero_Destino);
    cerrar = close(Fichero_Destino);

    execlp("bc", "bc", NULL);

  }else{

    cerrar = close(Tuberia_P2H[0]);
    Comprobar_Error(cerrar, "Error al cerrar la Tuberia_P2H[0].");
    cerrar = close(Tuberia_H2P[1]);
    Comprobar_Error(cerrar, "Error al cerrar la Tuberia_H2P[1].");

    while (index != 0) {
      usleep(500);
      memset(operacion, '\0', 50);
      index = Leer_Operacion(Fichero_Origen, Fichero_Destino, operacion);

      if (index == 1) {
        write(1, operacion, sizeof(operacion));
        escribir = write(Tuberia_P2H[1], operacion, strlen(operacion));
      }
    }
    escribir = write(Tuberia_P2H[1], "quit\n", 5);
  }

  return 0;
}
