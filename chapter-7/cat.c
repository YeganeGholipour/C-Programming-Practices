#include <stdio.h>

void filecopy(FILE *, FILE *);

void filecopy(FILE *fp, FILE *output) {
  int c;
  while ((c = fgetc(fp)) != EOF) {
    fputc(c, output);
  }
}

int main(int argc, char *argv[]) {
  FILE *fp;

  if (argc == 1)
    filecopy(stdin, stdout);
  else
    while (--argc > 0) 
        if ((fp = fopen(*++argv, "r")) == NULL) {
            printf("cat: can't open %s\n", *argv);
            return 1;
        } else {
            filecopy(fp, stdout);
            fclose(fp);

        }
    return 0;
}

