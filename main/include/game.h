#ifndef __GAME_H_
#define __GAME_H_

#include "bmp.h"
#include "dir.h"
#include "touch.h"
#include <time.h>
#include "font.h"
#define line 4
#define GAME_PATH "./res/game/"
extern int key;
extern char* p;
extern struct coord coor;
void Game_Init();
void showimg(int data[line][line]);
void getRand(int data[line][line]);
void moveUp(int data[line][line]);
void moveDown(int data[line][line]);
void moveRight(int data[line][line]);
void moveLift(int data[line][line]);
int isGameOver(int data[line][line]);
int getScore(int data[line][line]);
int maxSroce(int data);
void game();


#endif // !__GAME_H_
