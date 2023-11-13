#ifndef __VIDEO_H_
#define __VIDEO_H_

#include "bmp.h"
#include "touch.h"
#include "dir.h"
#define VIDEO_MKFIFO		"/tmp/mk_video"
extern struct coord coor;
extern char* p;
extern int key;
int mplayer_init();
void write_cmd(int fd, char* cmd);
void video();

#endif // !__VIDEO_H_

