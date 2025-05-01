#ifndef DIRSYS_H
#define DIRSYS_H

#include "dirnet.h"

DIR *my_opendir(char *path);
void list_dir(const char *path);
void my_closedir(DIR *dp);

#endif