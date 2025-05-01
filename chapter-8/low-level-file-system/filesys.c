#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filesys.h"

#define PERM 0666

size_t _refill_buffer(size_t total_bytes, MY_FILE *stream);

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
    stream->buf_end = 0;
  }
  return 0;
}

size_t my_fread(void *ptr, size_t size, size_t nmemb, MY_FILE *stream) {
  if (!ptr || !stream || size == 0 || nmemb == 0 ||
      (stream->mode & (WRITE | APPEND)) || stream->error || stream->eof)
    return 0;

  size_t total_bytes = size * nmemb;
  size_t copied = 0;
  char *dest = (char *)ptr;

  while (copied < total_bytes) {
    if (stream->buf_pos >= stream->buf_end) {
      size_t n = read(stream->fd, stream->buffer, stream->bufsize);
      if (n <= 0) {
        if (n == 0)
          stream->eof = 1;
        else
          stream->error = 1;
        break;
        stream->buf_pos = 0;
        stream->buf_end = n;
      }
    }

    size_t available = stream->buf_end - stream->buf_pos;
    size_t needed = total_bytes - copied;
    size_t to_copy = (available < needed) ? available : needed;

    memcpy(dest + copied, stream->buffer + stream->buf_pos, to_copy);
    copied += to_copy;
    stream->buf_pos += to_copy;
  }

  return copied / size;
}

size_t my_fwrite(const void *ptr, size_t size, size_t nmemb, MY_FILE *stream) {
  if (!ptr || !stream || size == 0 || nmemb == 0 || (stream->mode & READ) ||
      stream->error || stream->eof)
    return 0;

  size_t total_bytes = size * nmemb;
  size_t copied = 0;
  const char *src = (const char *)ptr;

  while (copied < total_bytes) {
    if (stream->buf_pos >= stream->bufsize) {
      if (my_fflush(stream) == EOF)
        break;
    }

    size_t available = stream->bufsize - stream->buf_pos;
    size_t needed = total_bytes - copied;
    size_t to_be_copied = (available < needed) ? available : needed;

    memcpy(stream->buffer + stream->buf_pos, src + copied, to_be_copied);
    stream->buf_pos += to_be_copied;
    copied += to_be_copied;
  }

  return copied / size;
}

int fseek(MY_FILE *stream, long int offset, int whence) {
  if (!stream || stream->error || stream->eof)
    return -1;

  int real_whence;
  switch (whence) {
  case MY_SEEK_SET:
    real_whence = SEEK_SET;
    break;
  case MY_SEEK_CUR:
    real_whence = SEEK_CUR;
    break;
  case MY_SEEK_END:
    real_whence = SEEK_END;
    break;
  default:
    stream->error = 1;
    return -1;
  }

  // Flush first in WRITE mode to prevent writing at wrong offset
  if (stream->mode == WRITE) {
    if (my_fflush(stream) == EOF) {
      stream->error = 1;
      return -1;
    }
  }

  if (lseek(stream->fd, offset, real_whence) == -1) {
    stream->error = 1;
    return -1;
  }

  // Invalidate buffer in READ mode
  if (stream->mode == READ) {
    stream->buf_pos = 0;
    stream->buf_end = 0;
  }

  return 0;
}
