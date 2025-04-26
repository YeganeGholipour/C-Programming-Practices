#include "my_file.h"
#include <stdio.h>

int main() {
  my_FILE *f = my_fopen("text.txt");
  if (!f) {
    perror("my_fopen");
    return -1;
  }

  int c;
  while ((c = my_fgetc(f)) != -1)
  {
    putchar(c);
  }

  my_fclose(f);
  return 0;
  
}