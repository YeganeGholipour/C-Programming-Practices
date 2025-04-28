#ifndef FILESYS_H
#define FILESYS_H

#include <stddef.h>

#define MY_BUFSIZ 4096

typedef enum { READ, WRITE, APPEND } mode;

typedef struct {
  int fd;         // file descriptor
  char *buffer;   // I/O buffer
  size_t bufsize; // total buffer size
  int buf_pos;    // current position inside buffer
  int buf_end;    // number of valid bytes in buffer
  int mode;       // read / write / append mode
  int eof;        // end-of-file flag
  int error;      // error flag
} MY_FILE;

// calls open()
MY_FILE *my_fopen(char *file_name, int mode);
// calls close()
int my_fclose(MY_FILE *stream);
// reads from buffer, refill if needed
int my_fgetc(MY_FILE *stream);
// writes into buffer, flush if full
int my_fputc(int c, MY_FILE *stream);
// flush write buffer
int my_fflush(MY_FILE *stream);

#endif