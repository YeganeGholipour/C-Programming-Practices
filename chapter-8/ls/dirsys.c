#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "dirnet.h"

DIR *my_opendir(char *dirname) {
  int fd;
  struct stat stbuf;
  DIR *dp;

  if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 ||
      (stbuf.st_mode & __S_IFMT) != __S_IFDIR ||
      (dp = (DIR *)malloc(sizeof(DIR))) == NULL)
    return NULL;

  dp->fd = fd;
  return dp;
}

void my_closedir(DIR *dp) {
  if (dp) {
    close(dp->fd);
    free(dp);
    dp = NULL;
  }
}


/************************** OLD-SCHOOL VERSION (DOES NOT WORK ANYMORE ON SYSTEM-D)*********
 * DIRNET *my_readdir(DIR *dp) {
  struct direct dirbuf;
  static DIRNET d;

  while (read(dp->fd, (char *)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
    if (dirbuf.d_ino == 0)
      continue;
    d.ino = dirbuf.d_ino;
    strncpy(d.name, dirbuf.d_name, DIRSIZ);
    d.name[DIRSIZ] = '\0';
    return &d;
  }
  return NULL;
}
******************************************************************************************/
