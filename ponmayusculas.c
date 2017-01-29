#include <unistd.h>

char in;
int leidos=1,escritos=0;

int main() {
  while (leidos!=0)
    {
      leidos=read(0,&in,1);
      if (leidos==1)
	{
	  if ((in>='a')&&(in<='z'))
	    in=in-(char)32;
	  /* con las Ã± nos metemos en caracteres que se representan
	     con mÃ¡s de un byte, asi que lo dejamos
	  else if (in=='Ã±') in='Ã‘';
	  */
	}
      escritos=write(1,&in,1);
    }
  _exit(37);
}
