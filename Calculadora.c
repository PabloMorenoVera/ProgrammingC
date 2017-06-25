// Pablo Moreno Vera
// Doble Grado IST y ADE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

static void Comprobar_Error(int Check, char error[]) {
  if (Check == -1) {
    perror(error);
    exit(EXIT_FAILURE);
  }
}

char Convertir_simbolo(char op[]){

  if (strcmp(op, "SUM") == 0) {
    return '+';
  }else if (strcmp(op, "SUB") == 0) {
    return '-';
  }else if (strcmp(op, "DIV") == 0) {
    return '/';
  }else if (strcmp(op, "MUL") == 0) {
    return '*';
  }else{
    perror("Error al convertir el símbolo.");
    exit(EXIT_FAILURE);
  }
}

int Leer_Operacion(int Fichero_O, int Fichero_D, char operacion[]){
  int leer = -1, escribir = -1;
  char c, op[5] = "";

  leer = read(Fichero_O, &c, sizeof(c));
  Comprobar_Error(leer, "Error al leer del fichero.");

  if (c == '/') {
    while(c != '\n'){
      leer = read(Fichero_O, &c, sizeof(c));
      Comprobar_Error(leer, "Error al leer del fichero.");
    }
    return -2;
  }else if (leer == 0) {
    return -1;
  }else{
    operacion[0] = c;

    leer = read(Fichero_O, &operacion[1], sizeof(c));
    Comprobar_Error(leer, "Error al leer del fichero.");

    for (size_t i = 0; i < 3; i++) {
      leer = read(Fichero_O, &op[i], sizeof(c));
      Comprobar_Error(leer, "Error al leer del fichero.");
    }

    operacion[2] = Convertir_simbolo(op);

    leer = read(Fichero_O, &operacion[3], sizeof(c));
    Comprobar_Error(leer, "Error al leer del fichero.");

    leer = read(Fichero_O, &operacion[4], sizeof(c));
    Comprobar_Error(leer, "Error al leer del fichero.");

    escribir = write(Fichero_D, operacion, strlen(operacion));
    Comprobar_Error(escribir, "Error al escribir la operacion en el fichero destino.");

    escribir = write(Fichero_D, " = ", 3);
    Comprobar_Error(escribir, "Error al escribir la operacion en el fichero destino.");

    while (c != '\n') {
      leer = read(Fichero_O, &c, sizeof(c));
      Comprobar_Error(leer, "Error al leer del fichero.");
    }

    operacion[5] = '\n';
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  int Fichero_Origen = -1, Fichero_Destino = -1, Hijo = -1;
  int tuberia_padre[2], tuberia_hijo[2];
  int abrir = -1, cerrar = -1, escribir = -1, leer = -1;
  int index = -3, Num_Linea = 0, Num_Operacion = 0, status, options = 0;
  char operacion[50] = "";

  if (argc != 3) {
    perror("Introduce dos argumentos: Fichero_Origen Fichero_Destino.");
    exit(EXIT_FAILURE);
  }

  Fichero_Origen = open(argv[1], O_RDONLY);
  Comprobar_Error(Fichero_Origen, "Error al abrir Fichero_Origen");

  Fichero_Destino = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
  Comprobar_Error(Fichero_Destino, "Error al abrir Fichero_Destino.");

  abrir = pipe(tuberia_padre);
  Comprobar_Error(abrir, "Error al abrir la tuberia padre.");

  abrir = pipe(tuberia_hijo);
  Comprobar_Error(abrir, "Error al abrir la tuberia hijo.");

  Hijo = fork();

  if (Hijo == 0) {

    cerrar = close(tuberia_padre[1]);
    Comprobar_Error(cerrar, "Error al cerrar la tuberia padre[1]");
    cerrar = close(tuberia_hijo[0]);
    Comprobar_Error(cerrar, "Error al cerrar la tuberia hijo[0]");

    cerrar = close(0);
    dup(tuberia_padre[0]);
    close(tuberia_padre[0]);

    cerrar = close(1);
    dup(Fichero_Destino);
    close(Fichero_Destino);

    execlp("bc", "bc", NULL);
/*
    leer = read(tuberia_padre[0], operacion, sizeof(operacion));
    Comprobar_Error(leer, "Error al leer de la tuberia la operación");

    write(1, operacion, sizeof(operacion));
*/
  }else{

    cerrar = close(tuberia_padre[0]);
    Comprobar_Error(cerrar, "Error al cerrar la tuberia padre[0]");
    cerrar = close(tuberia_hijo[1]);
    Comprobar_Error(cerrar, "Error al cerrar la tuberia hijo[1]");

    while (index != -1) {
      usleep(500);
      memset(operacion, '\0', 50);
      index = Leer_Operacion(Fichero_Origen, Fichero_Destino, operacion);

      if (index == 0) {
        escribir = write(tuberia_padre[1], operacion, strlen(operacion));
        Comprobar_Error(escribir, "Error al enviar la operación por la tubería.");

        Num_Operacion = Num_Operacion + 1;
      }else if (index == -1) {
        escribir = write(tuberia_padre[1], "quit\n", 5);
        Comprobar_Error(escribir, "Error al enviar la operación por la tubería.");
      }
      Num_Linea = Num_Linea + 1;
    }
    waitpid(Hijo, &status, options);
    if (WIFEXITED(status)) {
      printf("Se han contado %d líneas, %d operaciones.\n", Num_Linea, Num_Operacion);
      printf("El valor de retorno del hijo es %d\n", WEXITSTATUS(status));
    }
  }

  return 0;
}
