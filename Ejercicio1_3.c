#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

pid_t pid;
int status = 0;

pid = fork();

if (pid == 0) {
  /*Rama del hijo*/
  execl("/bin/ls", "ls", "/home/pablo", NULL);
  return 0;
}else{
  /*Rama del padre*/
  waitpid(pid, &status, 0);
  execl("/bin/cat", "cat", "Ejercicio1_3.c", NULL);
}

  return 0;
}
