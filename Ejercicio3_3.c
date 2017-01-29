  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <string.h>

int main(int argc, char const *argv[]) {

  int Fichero1 = 0, Fichero2 = 0, numbytes = 0, escribir = 0, leer = 0;
  int Buffer[1024];
  char Buffer1[15];
  char Nombre_Fd1[7], Nombre_Fd2[7];

  if (argc == 1) {
    leer = read(0, Buffer1,sizeof(Buffer1));
    if (leer == -1) {
      perror("¡¡ERROR!!, Introduzca(7 caracteres/fichero): Nombre_Fichero_Origen Nombre_Fichero_Destino");
      exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < 7; i++) {
      Nombre_Fd1[i] = Buffer1[i];
    }
    for (size_t i = 8; i < 15; i++){
      Nombre_Fd2[i-8] = Buffer1[i];
    }

    Fichero1 = open(Nombre_Fd1, O_RDONLY);
    if (Fichero1 == -1) {
      perror("Fallo al abrir fichero origen");
      exit(EXIT_FAILURE);
    }

    Fichero2 = open(Nombre_Fd2, O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
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

  }else{
    printf("Número de argumentos incorrecto, inttroduzca: ./Ejercicio3_3\n");
  }

  return 0;
}
