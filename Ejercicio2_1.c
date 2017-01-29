#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  int fd = 1;
  const char* Cadena = "Hola Mundo.\n";

 write(fd, Cadena, strlen(Cadena));

  return 0;
}
