#include "touch.h"
#include <string.h>

int touch_fd;
void Init_touch()
{
	touch_fd = open(TOUCH_PATH, O_RDONLY);
	if (-1 == touch_fd)
	{
		perror("open touch failed:");
		return;
	}
}
void UnInit_touch()
{
	close(touch_fd);
}

int get_xy(struct coord* coor)
{
	struct input_event ev;
	int flag = 0;
	int x_set = 0, y_set = 0;
	int x = 0, y = 0;
	int x_new = 0, y_new = 0;
	//printf("touch:%d\n", __LINE__);
	while (1)
	{

		read(touch_fd, &ev, sizeof(ev));
		//printf("touch:%d\n", __LINE__);
		//printf("%d\n",ev.type);
		if (ev.type == EV_ABS)
		{
			//printf("%d\n", __LINE__);
			//printf("%d\n",ev.value);
			if (ev.code == ABS_X)
			{
				coor->x = ev.value * 800 / 1024 ;
				x = coor->x;
			}if (ev.code == ABS_Y)
			{
				coor->y = ev.value * 480 / 600 ;
				y = coor->y;
			}
			//printf("%d,%d\n", coor->x, coor->y);
		}			
		else if (ev.type == EV_KEY&&ev.code == BTN_TOUCH)
		{
			coor->release = ev.value;
			if (ev.value == 1) x_set = x, y_set = y;
			else
			{
				printf("touch key :%d\n", __LINE__);				
				//printf("%d,%d\n",x,y);				
				x_new = x, y_new = y;
				printf("%d,%d\n",y_new - y_set,x_new - x_set);
				if (y_new - y_set < -80) return 1;		//up
				else if (y_new - y_set > 80) return 2;	//down
				else if (x_new - x_set < -80) return 3;	//left
				else if (x_new - x_set > 80)return 4;	//right
				else return 0;
			}
		}
		
		
	}
}