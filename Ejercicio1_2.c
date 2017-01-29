#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

  pid_t pid;
  int a = 10, b = 5, status = 0, options = 0;

  pid = fork();

  if (pid == 0) {
    /*Rama del hijo*/
    printf("Soy el hijo con mi pid: %d y sumo a + b\n", getpid());
    exit(a + b);
  }else{
    /*Rama del padre*/
    waitpid(pid, &status, options);
    if (WIFEXITED(status)) {
      printf("Mi hijo me pasa el valor de a(10) + b(5) es %d\n",  WEXITSTATUS(status));
    }else{
      printf("El hijo no ha terminado correctamente\n");
    }
  }

  return 0;
}
