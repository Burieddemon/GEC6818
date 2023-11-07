#include "album.h"
extern int key;
extern struct coord coor;
extern char* p;
void showphoto()
{
	int num = 0;
	char** file = isdir("./res/photo",&num);
	int i = 0;
	while (1)
	{
		//bmpclean(p);
		if (key == 3 && coor.release == 0)
		{
			bmp2lcd(file[i],p,0,0);
			i++;
			if (i > num)
				i = 0;
			key =0;			
		}
		if (key == 4&&coor.release == 0)
		{
			bmp2lcd(file[i], p, 0, 0);
			i--;
			if (i < 0)
				i = num-1;	
			key = 0;		
		}
		if (coor.x>750&&coor.y<50)
		{
			break;
		}
	}
}
