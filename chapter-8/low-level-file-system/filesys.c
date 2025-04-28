#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "filesys.h"

#define PERM 0666

MY_FILE *my_fopen(char *file_name, int mode) {
  int fd, flag;
  MY_FILE *fp;

  if (file_name == NULL) {
    fprintf(stderr, "my_fopen: no filename is specified\n");
    return NULL;
  }

  if ((fp = (MY_FILE *)malloc(sizeof(MY_FILE))) == NULL) {
    fprintf(stderr, "my_fopen: memory allocation failed\n");
    return NULL;
  }

  switch (mode) {
  case READ:
    flag = O_RDONLY;
    break;

  case WRITE:
    flag = O_WRONLY | O_CREAT | O_TRUNC;
    break;

  case APPEND:
    flag = O_WRONLY | O_CREAT | O_APPEND;
    break;

  default:
    fprintf(stderr, "usage: unknown flag\n");
    free(fp);
    return NULL;
  }

  if ((fd = open(file_name, flag, PERM)) == -1) {
    fprintf(stderr, "my_fopen: cannot open file %s\n", file_name);
    free(fp);
    return NULL;
  }

  fp->fd = fd;
  fp->buffer = malloc(MY_BUFSIZ);
  if (fp->buffer == NULL) {
    close(fp->fd);
    free(fp);
    return NULL;
  }

  fp->bufsize = MY_BUFSIZ;
  fp->buf_pos = 0;
  fp->buf_end = 0;
  fp->mode = mode;
  fp->eof = 0;
  fp->error = 0;

  return fp;
}

int my_fclose(MY_FILE *stream) {
  int flush_result = 0;
  int close_result = 0;

  if (!stream)
    return EOF;

  if (stream->mode == WRITE || stream->mode == APPEND)
    flush_result = my_fflush(stream);

  close_result = close(stream->fd);

  if (stream->buffer) {
    free(stream->buffer);
    stream->buffer = NULL;
  }

  stream->fd = -1;
  stream->bufsize = 0;
  stream->buf_pos = 0;
  stream->buf_end = 0;
  stream->mode = 0;
  stream->eof = 1;
  stream->error = 1;

  free(stream);
  stream = NULL;

  if (flush_result == EOF || close_result == -1)
    return EOF;
  else
    return 0;
}

int my_fgetc(MY_FILE *stream) {
  if (stream->buf_pos >= stream->buf_end) {
    size_t read_bytes = read(stream->fd, stream->buffer, stream->bufsize);
    if (read_bytes <= 0) {
      stream->eof = 1;
      return EOF;
    }
    stream->buf_pos = 0;
    stream->buf_end = read_bytes;
  }

  return (unsigned char)stream->buffer[stream->buf_pos++];
}

int my_fputc(int c, MY_FILE *stream) {
  if (stream->buf_pos >= stream->bufsize) {
    if (my_fflush(stream) == EOF)
      return EOF;
  }

  stream->buffer[stream->buf_pos++] = (unsigned char)c;

  return 0;
}

int my_fflush(MY_FILE *stream) {
  if (stream->buf_pos > 0) {
    if (write(stream->fd, stream->buffer, stream->buf_pos) != stream->buf_pos) {
      stream->error = 1;
      return EOF;
    }

    stream->buf_pos = 0;
  }
  return 0;
}
