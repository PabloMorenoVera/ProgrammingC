#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

  int numbytes, escribir, fichero = 0, count = 3;
  int Buffer[30];

  numbytes = read(fichero, Buffer, sizeof(Buffer));
  if (numbytes == -1) {
    perror("Fallo al leer del terminal");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < count; i++) {
    escribir = write(fichero, Buffer, numbytes);
    if (escribir == -1) {
      perror("Fallo al escribir en el terminal");
      exit(EXIT_FAILURE);
    }
  }

  return 0;
}
