#ifndef __DIR_H_
#define __DIR_H_

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

char** isdir(char* path, int* num);
#endif
