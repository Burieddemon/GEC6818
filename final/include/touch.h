#pragma once
#ifndef __TS_H_
#define __TS_H_

#include <dirent.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define TOUCH_PATH "/dev/input/event0"
#define WIDTH 800
#define HEIGHT 480

struct coord
{
	int x;
	int y;
	bool release;
};

void Init_touch();
void UnInit_touch();
int get_xy(struct coord* coor);


#endif
