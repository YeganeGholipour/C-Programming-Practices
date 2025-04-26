#include "my_file.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

my_FILE *my_fopen(const char *path) {
  int fd = open(path, O_RDONLY);
  if (fd < 0)
    return NULL;

  my_FILE *f = malloc(sizeof(my_FILE));
  if (!f) {
    close(fd);
    return NULL;
  }

  f->fd = fd;
  f->buf_pos = 0;
  f->buf_end = 0;
  f->eof = 0;

  return f;
}

int my_fgetc(my_FILE *f) {
  if (f->eof)
    return EOF;

  if (f->buf_pos >= f->buf_end) {
    int bytes_read = read(f->fd, f->buffer, MY_BUFSIZE);
    if (bytes_read <= 0) {
      f->eof = 1;
      return EOF;
    }
    f->buf_pos = 0;
    f->buf_end = bytes_read;
  }

  return (unsigned char)f->buffer[f->buf_pos++];
}

int my_fclose(my_FILE *f) {
  int ret = close(f->fd);
  free(f);
  return ret;
}