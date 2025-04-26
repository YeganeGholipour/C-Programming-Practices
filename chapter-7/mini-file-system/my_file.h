#ifndef MY_FILE_H
#define MY_FILE_H

#define MY_BUFSIZE 4096

typedef struct {
    int fd;                      // File descriptor
    char buffer[MY_BUFSIZE];     // Buffer for file content
    int buf_pos;                 // Current read position
    int buf_end;                 // Number of valid bytes in buffer
    int eof;                     // EOF flag
} my_FILE;


my_FILE *my_fopen(const char *path);
int my_fgetc(my_FILE *f);
int my_fclose(my_FILE *f);


#endif