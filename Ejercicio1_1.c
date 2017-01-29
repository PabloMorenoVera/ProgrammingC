#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid1, pid2;
  int status1, status2, options1=0, options2=0;

  if ((pid1 = fork()) == 0) {
    /*Rama del primer hijo*/
    printf("Hola soy el hijo 1 y mi pid es %d\n", getpid());
  }else{
    if ((pid2 = fork()) == 0) {
      /*Rama del segundo hijo*/
      printf("Hola soy el hijo 2 y mi pid es %d\n", getpid());
    }else{
      /*Rama del padre*/
      printf("Hola soy el padre.\n");
      waitpid(pid1, &status1, options1);
      waitpid(pid2, &status2, options2);
      printf("Mis hijos son: Hijo1: %d e Hijo2: %d \n", pid1, pid2);
      printf("Ya han terminado todos mis hijos\n");
    }
  }
  return 0;
}
