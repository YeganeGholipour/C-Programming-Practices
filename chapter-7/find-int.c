#include <stdio.h>

int find_int(const char *filename) {
  FILE *fp = fopen(filename, "r");
  int n;

  if (fp == NULL)
    return -1; // cannot open file

  while (fscanf(fp, "%d", &n) != 1) {
    if (ferror(fp)) {
      fclose(fp);
      return -2; // read error
    }
    if (feof(fp)) {
        fclose(fp);
        return -3;
    }
    fscanf(fp, "%*[^\n]");
  }

  fclose(fp);
  return n;
}