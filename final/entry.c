#include "touch.h"
#include "bmp.h"
#include "dir.h"
#include "album.h"
#include "music.h"
#include "video.h"
#include "game.h"
#define LCD_PATH "/dev/fb0"

struct coord coor;
int key;
char* p = NULL;
void* pthread_get_xy(void* arg)
{
	printf("%d\n",__LINE__);
	while (1)
	{
		key = get_xy(&coor);
		sleep(1);
	}
}


int main()
{
	Init_touch();
	pthread_t pid;
	pthread_create(&pid, NULL, pthread_get_xy, NULL);
	int lcd_fd = open(LCD_PATH, O_RDWR);
	p = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if (MAP_FAILED == p)
	{
		perror("open lcd failed");
		return 0;
	}
	bmpclean(p);
	//bmp2lcd("1.bmp", p, 0, 0);
	//char** file = isdir(".");
	//int i = 0;
	/*while (strlen(file[i])== 0)
	{
		printf("%s\n", file[i]);
		i++;
	}*/
	bmp2lcd("./res/home.bmp", p, 0, 0);
	printf("%d,%d\n", coor.x, coor.y);
	printf("entry:%d\n",__LINE__);
	while (1)
	{
		//sleep(1);
		//printf("%d,%d\n", coor.x, coor.y);
		//pthread_create(&pid, NULL, pthread_get_xy, NULL);
		if (coor.x > 100 && coor.x < 250 && coor.y>50 && coor.y < 150)
		{
			printf("相册\n");
			memset(p, 0, 800 * 480 * 4);
			showphoto();
			memset(p, 0, 800 * 480 * 4);
			bmp2lcd("./res/home.bmp", p, 0, 0);
		}
		if (coor.x > 550 && coor.x < 700 && coor.y>50 && coor.y < 150)
		{
			printf("音乐播放器\n");
			memset(p, 0, 800 * 480 * 4);
			music();
			memset(p, 0, 800 * 480 * 4);
			bmp2lcd("./res/home.bmp", p, 0, 0);
		}
		if (coor.x > 100 && coor.x < 250 && coor.y>300 && coor.y < 400)
		{
			printf("视频播放器\n");
			video();
			bmp2lcd("./res/home.bmp", p, 0, 0);
		}
		if (coor.x > 550 && coor.x < 700 && coor.y>300 && coor.y < 400)
		{
			printf("2048\n");
			game();
			bmp2lcd("./res/home.bmp", p, 0, 0);
		}
		else
		{
			continue;
		}
	}
	UnInit_touch();
	return 0;

}