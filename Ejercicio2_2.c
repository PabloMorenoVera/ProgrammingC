#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  int Fichero1, Fichero2, numbytes, escribir;
  int Buffer[1024];


  Fichero1 = open("Fichero1.txt", O_RDONLY);
  if (Fichero1 == -1) {
    perror("Fallo al abrir fichero origen");
    exit(EXIT_FAILURE);
  }

  Fichero2 = open("Fichero2.txt", O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
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
  return 0;
}
