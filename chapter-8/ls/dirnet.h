#ifndef DIRNET_H
#define DIRNET_H

#define NAME_MAX 14 /* longest filename component; system-dependent*/

typedef struct {           /* directory entry */
  long ino;                /* inode number */
  char name[NAME_MAX + 1]; /* name */
} DIRNET;

typedef struct {
  int fd;
  DIRNET d;
} DIR;

#endif
