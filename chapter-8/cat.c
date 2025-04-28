#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define PERMS 0666

void filecopy(int, int);

void filecopy(int input_fd, int output_fd) {
  int n;
  char buf[BUFSIZ];

  while ((n = read(input_fd, buf, BUFSIZ)) > 0)
    if (write(output_fd, buf, n) != n)
      printf("error!");
}

int main(int argc, char const *argv[]) {
  int fd;

  if (argc == 1)
    filecopy(0, 1);
  else {
    while (--argc > 0)
      if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
        printf("cat: can't open %s\n", *argv);
        return 1;
      } else {
        filecopy(fd, 1);
        close(fd);
      }
  }
  return 0;
}
