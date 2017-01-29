#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void abrir_tuberia (int tuberia[]){
  int abrir = -1;

  abrir = pipe(tuberia);
  if (abrir == -1) {
    perror("Error al abrir la tubería.");
    exit(EXIT_FAILURE);
  }
}

void cerrar_tuberia(int tuberia[], int i){
  int cerrar = -1;

  cerrar = close(tuberia[i]);
  if (cerrar == -1) {
    perror("Error al cerrar la tubería.");
    exit(EXIT_FAILURE);
  }
}

int abrir_fichero(char Fichero[]){
  int abrir = -1;

  abrir = open(Fichero, O_RDONLY);
  if (abrir == -1) {
    perror("Error al abrir el archivo.");
    exit(EXIT_FAILURE);
  }
  return abrir;
}

int abrir_fichero_escr(char Fichero[]){
  int abrir = -1;

  abrir = open(Fichero, O_WRONLY);
  if (abrir == -1) {
    perror("Error al abrir el archivo.");
    exit(EXIT_FAILURE);
  }
  return abrir;
}

void trocear_frase (int Archivo, char Palabra[], char c, int i){
  char caracter = '0';
  int leer = -1;

  while (caracter != c) {
    leer = read(Archivo, &caracter, sizeof(caracter));
    if (leer == -1) {
      perror("Error al leer del archivo CmdFile.");
      exit(EXIT_FAILURE);
    }
    if (caracter != c) {
      Palabra[i] = caracter;
    }
    i = i+1;
  }
}

void enviar_comandos(char Palabra[], int tuberia[], int i){
  int escribir = -1;
  char Buffer[1024] = "";

  strcpy(Buffer, Palabra);

  escribir = write(tuberia[i], Buffer, sizeof(Buffer));
  if (escribir == -1) {
    perror("Error al enviar los comandos.");
    exit(EXIT_FAILURE);
  }
}

void leer_comandos(int tuberia[], int i, char Palabra[]){
  int leer = -1;
  char Buffer[1024] = "";

  leer = read(tuberia[i], Buffer, sizeof(Buffer));
  if (leer == -1) {
    perror("Error al leer los comandos.");
    exit(EXIT_FAILURE);
  }
  strcpy(Palabra, Buffer);
}

void conseguir_comando(char D_comando[], char Comando[]){
  char c = '/';
  int salir = 0, i = 5, j = 0;

  while (D_comando[i] != '\0') {
    Comando[j] = D_comando[i];
    j++; i++;
  }
}

void cerrar_descriptor(int i){
  int cerrar = -1;

  cerrar = close(i);
  if (cerrar == -1) {
    perror("Error al cerrar el descriptor de fichero %d, i");
    exit(EXIT_FAILURE);
  }
}

void ejecutar_comando(char Comando[], char Dir_Comando[], char F_Origen[]){
  int ejecucion = -1;

  ejecucion = execl(Dir_Comando, Comando, F_Origen, NULL);
  if (ejecucion == -1) {
    perror("Error al ejecutar el comando.");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char const *argv[]) {
  pid_t Hijo = 0;
  int tuberia_padre[1], tuberia_hijo[1], status = 0;
  int longitud = 0, i = 0, N_Fichero = 0, Dir_Fichero_O = 0, Dir_Fichero_D = 0;
  char Dir_Comando[50] = "", F_Origen[50] = "", F_Destino[50] = "", Comando[10] = "";
  char Nombre_Fichero[15] = "CmdFile.txt", espacio = ' ', finlinea = '\n';

  abrir_tuberia(tuberia_padre);
  abrir_tuberia(tuberia_hijo);

  Hijo = fork();

  if (Hijo == 0) {
    //Rama hijo.

    cerrar_tuberia(tuberia_padre, 1);
    cerrar_tuberia(tuberia_hijo, 0);

    leer_comandos(tuberia_padre, 0, Dir_Comando);
    leer_comandos(tuberia_padre, 0, F_Origen);
    leer_comandos(tuberia_padre, 0, F_Destino);

    conseguir_comando(Dir_Comando, Comando);

    Dir_Fichero_O = abrir_fichero(F_Origen);
    cerrar_descriptor(0);
    dup(Dir_Fichero_O);
    cerrar_descriptor(Dir_Fichero_O);

    Dir_Fichero_D = abrir_fichero_escr(F_Destino);
    cerrar_descriptor(1);
    dup(Dir_Fichero_D);
    cerrar_descriptor(Dir_Fichero_D);

    ejecutar_comando(Comando, Dir_Comando, F_Origen);

  }else{
    //Rama padre

    cerrar_tuberia(tuberia_padre, 0);
    cerrar_tuberia(tuberia_hijo, 1);

    N_Fichero = abrir_fichero(Nombre_Fichero);

    trocear_frase(N_Fichero, Dir_Comando, espacio, i);
    trocear_frase(N_Fichero, F_Origen, espacio, i);
    trocear_frase(N_Fichero, F_Destino, finlinea, i);
    printf("%s\n%s\n%s\n", Dir_Comando, F_Origen, F_Destino);

    enviar_comandos(Dir_Comando, tuberia_padre, 1);
    enviar_comandos(F_Origen, tuberia_padre, 1);
    enviar_comandos(F_Destino, tuberia_padre, 1);

    waitpid(Hijo, &status, 0);  //Si espera es 0, entonces continnuo con el bucle de ejecución de los siguientes comandos.
    if (WIFEXITED(status)) {
      printf("Ejecución correcta.\n");
    }else{
      printf("Ejecución incorrecta.\n");
    }

  }

  return 0;
}
