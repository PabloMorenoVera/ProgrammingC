#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  int Fichero1 = 0, Fichero2 = 0, numbytes = 0, escribir = 0;
  int Buffer[1024];

  if (argc == 3) {
    Fichero1 = open(argv[1], O_RDONLY);
    if (Fichero1 == -1) {
      perror("Fallo al abrir fichero origen");
      exit(EXIT_FAILURE);
    }

    Fichero2 = open(argv[2], O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    if (Fichero2 == -1) {
      perror("Fallo al abrir fichero destino");
      exit(EXIT_FAILURE);
    }

    numbytes = read(Fichero1, Buffer, sizeof(Buffer));
    while (numbytes > 0) {
      escribir = write(Fichero2, Buffer, numbytes);
      if (escribir == -1) {
        perror("Fallo al escribir en el fichero destino");
        exit(EXIT_FAILURE);
      }
      numbytes = read(Fichero1, Buffer, sizeof(Buffer));
    }

    if (close(Fichero1) == -1) {
      perror("Fallo al cerrrar fichero origen");
      exit(EXIT_FAILURE);
    }
    if (close(Fichero2) == -1) {
      perror("Fallo al cerrrar fichero destino");
      exit(EXIT_FAILURE);
    }
  }else if (argc == 2) {

    Fichero1 = open(argv[1], O_RDONLY);
    if (Fichero1 == -1) {
      perror("Fallo al abrir el fichero destino");
      exit(EXIT_FAILURE);
    }

    numbytes = read(Fichero1, Buffer, sizeof(Buffer));
    while (numbytes > 0) {
      escribir = write(1, Buffer, numbytes);
      if (escribir == -1) {
        perror("Fallo al escribir en fichero destino");
        exit(EXIT_FAILURE);
      }
      numbytes = read(Fichero1, Buffer, sizeof(Buffer));
    }

    if (close(Fichero1) == -1) {
      perror("Fallo al cerrar el fichero desti  no");
      exit(EXIT_FAILURE);
    }

  }else{
    printf("Número de argumentos incorrecto, por favor introduzca: \n");
    printf("1) Nombre_Programa, Fichero_Origen, Fichero_Destino\n");
    printf("2) Nombre_Programa, Fichero_Origen\n");
    exit(0);
  }

  return 0;
}
