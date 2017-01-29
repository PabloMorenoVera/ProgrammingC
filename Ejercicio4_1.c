#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void abrir_tuberia(int tuberia[]){
  int abrir = -1;

    abrir = pipe(tuberia);
    if (abrir == -1) {
      perror("Error al abrir tuberia.");
      exit(EXIT_FAILURE);
    }
}

void cerrar_tuberia(int tuberia[], int a){
  int cerrar = -1;

  cerrar = close(tuberia[a]);
  if (cerrar == -1) {
    perror("Error al cerrar la tubería.");
    exit(EXIT_FAILURE);
  }
}

int asignar_comandos(char Cadena[], char Frase[], int j){
  int i = 0;

  while (Frase[j] != ' ') {
    if (Frase[j] == '\n') {
      break;
    }
    Cadena[i] = Frase[j];
    j++;
    i++;
  }
  return ++j;
}

/*void conseguir_comando(char Comando[], char Dir_Comando[]){
  int i = 1, asignar = 0;

  while (i <= strlen(Dir_Comando)) {
    if (Dir_Comando[i] = '/') {
      asignar = 1;
    }
    if (asignar == 1) {
      Comando[i] = Dir_Comando[i];

    }
    ++i;
  }
printf("%s\n", Dir_Comando);
printf("%s\n", Comando);
}
*/
void abrir_fichero(char Nombre[], int i){
  int Fichero = -1;

  if (i == 1) {
    Fichero = open(Nombre, O_RDONLY);
  }else{
    Fichero = open(Nombre, O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
  }
  if (Fichero == -1) {
    perror("Erro al abrir el fichero");
    exit(EXIT_FAILURE);
  }
}

/*void enviar_comandos(int Tuberia[], int i, char Cadena[]){
  int  escribir = -1;
  char Buffer[1024];

  strcpy(Buffer, Cadena);
printf("%s\n", Buffer);
  escribir = write(Tuberia[i], Buffer, sizeof(Buffer));
  if (escribir == -1) {
    perror("Error el enviar los comandos al hijo.");
    exit(EXIT_FAILURE);
  }
}*/

int main(int argc, char const *argv[]) {
  pid_t hijo = -1;
  int tuberia_padre[1], tuberia_hijo[1];
  int CmdFile = -1, leer = -1, escribir = -1, esperar = -1, terminar = -1;
  int i = 0, j = 0, status = 0;
  char c;
  char Buffer_padre[1024], Buffer_hijo[1024];
  char Frase[800], Dir_Comando[100] , Comando[100], Fichero_D[100], Fichero_O[100];

  abrir_tuberia(tuberia_padre);
  abrir_tuberia(tuberia_hijo);

  hijo = fork();

  if (hijo == 0) {
    /*Rama hijo*/
    cerrar_tuberia(tuberia_hijo, 0);
    cerrar_tuberia(tuberia_padre, 1);

    leer = read (tuberia_padre[0], Buffer_hijo, sizeof(Buffer_hijo));
    if (leer == -1) {
      perror("Error al leer los comands en el hijo");
      exit(EXIT_FAILURE);
    }

    strcpy(Dir_Comando, Buffer_hijo);
printf("leer1: %s\n", Dir_Comando);
    leer = read (tuberia_padre[0], Buffer_hijo, sizeof(Buffer_hijo));
    if (leer == -1) {
      perror("Error al leer los comands en el hijo");
      exit(EXIT_FAILURE);
    }

    strcpy(Fichero_O, Buffer_hijo);
printf("leer2: %s\n", Fichero_O);
    leer = read (tuberia_padre[0], Buffer_hijo, sizeof(Buffer_hijo));
    if (leer == -1) {
      perror("Error al leer los comands en el hijo");
      exit(EXIT_FAILURE);
    }

    strcpy(Fichero_D, Buffer_hijo);
printf("leer3: %s\n", Fichero_D);

  abrir_fichero(Fichero_O, 1);
  abrir_fichero(Fichero_D, 0);

//  conseguir_comando(Comando, Dir_Comando);

printf("%s\n", Dir_Comando);
printf("%s\n", Comando);
printf("%s\n", Fichero_O);

  terminar = execv(Dir_Comando, Comando, Fichero_O, NULL);
  if (terminar == -1) {
    perror("Ejecución incorrecta");
    exit(EXIT_FAILURE);
  }
  }else{
    /*Rama padre*/

    cerrar_tuberia(tuberia_hijo, 1);
    cerrar_tuberia(tuberia_padre, 0);

    CmdFile = open("CmdFile.txt", O_RDONLY);
    if (CmdFile == -1) {
      perror("Error al abir el fichero CmdFile.");
      exit(EXIT_FAILURE);
    }

    while (c != '\n') {
      leer = read(CmdFile, &c, sizeof(c));
      if (leer == -1) {
        perror("Error al leer el fichero CmdFile.");
        exit(EXIT_FAILURE);
      }
      Frase[i] = c;
      i++;
    }

    j = asignar_comandos(Dir_Comando, Frase, j);
    j = asignar_comandos(Fichero_O, Frase, j);
    j = asignar_comandos(Fichero_D, Frase, j);

//    enviar_comandos(tuberia_padre, 1, Comando);
    strcpy(Buffer_padre, Dir_Comando);
    escribir = write(tuberia_padre[1], Buffer_padre, sizeof(Buffer_padre));
    if (escribir == -1) {
      perror("Error el enviar los comandos al hijo.");
      exit(EXIT_FAILURE);
    }

//    enviar_comandos(tuberia_padre, 1, Fichero_O);
    strcpy(Buffer_padre, Fichero_O);
    escribir = write(tuberia_padre[1], Buffer_padre, sizeof(Buffer_padre));
    if (escribir == -1) {
      perror("Error el enviar los comandos al hijo.");
      exit(EXIT_FAILURE);
    }

//    enviar_comandos(tuberia_padre, 1, Fichero_D);
    strcpy(Buffer_padre, Fichero_D);
    escribir = write(tuberia_padre[1], Buffer_padre, sizeof(Buffer_padre));
    if (escribir == -1) {
      perror("Error el enviar los comandos al hijo.");
      exit(EXIT_FAILURE);
    }

    esperar = waitpid(hijo, &status, 0);
    if (esperar == -1) {
      perror("Error al finalizar la ejercución del hijo");
      exit(EXIT_FAILURE);
    }else{
      printf("Ejecución correcta\n");
    }

  }

  return 0;
}
