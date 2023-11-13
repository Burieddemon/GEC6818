#include "music.h"

void music()
{
	system("killall -9 mplayer \n");
	pid_t pid;
	int i = 0, num;
	char** filename = isdir("./res/music/", &num);
	int x , y ;
	char buf[1024];
	bmp2lcd("./res/musicback.bmp", p, 0, 0);
	int flag = 1;	
	int cir = 1;
	while (1)
	{
		x = coor.x, y = coor.y;
		if (y>400&&y<480)
		{
			if (x > 360 && x < 440)
			{
				sprintf(buf, "madplay %s &", filename[i]);
				system(buf);
				if (flag)
				{
					system("killall -CONT madplay");
					flag = 0;
				}
				else
				{
					system("killall -STOP madplay");
					flag = 1;				
				}
				printf("%s\n",filename[i] );
			}
			if (x > 220&& x < 300)
			{
				system("killall -9 madplay");
				i--;
				if (i < 0)
					i = num;
				sprintf(buf, "madplay %s &", filename[i]);
				printf("%s\n",filename[i] );
				system(buf);
			}
			if (x > 520 && x < 600)
			{
				system("killall -9 madplay");
				i++;
				if (i > num)
					i = 0;
				sprintf(buf, "madplay %s &", filename[i]);
				printf("%s\n",filename[i] );
				system(buf);
			}
			if (x<80&&y>400)
			{
				if (cir)
				{
					system("madplay ./res/music/*.mp3 -r -a -20 &");
					cir = 0;
				}
				else
				{
					system("madplay ./res/music/*.mp3 -z -a -20 &");
					cir = 1;
				}

			}
			coor.x = 0,coor.y = 0;
		}
		if (x>720&&y<80)
		{
			if(flag == 0)
				break;
			else
			{
				system("killall -9 madplay");
				break;
			}
		}

		
	}
}

