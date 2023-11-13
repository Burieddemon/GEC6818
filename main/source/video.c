#include "video.h"

int mplayer_init()
{
	if (access(VIDEO_MKFIFO,F_OK))
	{
		if (mkfifo(VIDEO_MKFIFO, 0777) == -1)
		{
			perror("mkfifo() failed:");
			exit(1);
		}
	}

	int mk_fd = open(VIDEO_MKFIFO, O_RDWR);
	if (-1 == mk_fd)
	{
		perror("open mk_video failed:");
		exit(1);
	}
	return mk_fd;
}

void write_cmd(int fd, char* cmd)
{
	write(fd, cmd, strlen(cmd));
}

void video()
{
	system("killall -9 madplay");
	int num = 0,i = 0;
	char** filename = isdir("./res/video",&num); 
	char buf[1024] = "0";
	int fifo_fd = mplayer_init();
	int x, y;
	int flag = 1;
	const char basic_mplayer[] = "mplayer -slave -quiet -input file=/tmp/mk_video -geometry 0:0 -zoom -x 800 -y 480 %s &";
	sprintf(buf, basic_mplayer, filename[i]);
	system(buf);
	while (1)
	{		
		x = coor.x, y = coor.y;
		usleep(100);
		if (y > 400)
		{
			if (x > 350&&x < 450) 
			{
				
				write_cmd(fifo_fd, "pause\n");
				printf("暂停\n");				
				bzero(buf,sizeof(buf));
				printf("key %d\n",key);				
			}

			else if(x>150&&x<250)
			{
				system("killall -9 mplayer");
				i--;
				if (i < 0)
					i = num;				
				sprintf(buf, basic_mplayer, filename[i]);
				system(buf);
				printf("%d\n",key);
				printf("上一部\n");
			}
			else if (x > 550 && x < 650)
			{
				system("killall -9 mplayer");
				i++;
				if (i > num)
					i = 0;
				sprintf(buf, basic_mplayer, filename[i]);
				system(buf);

				printf("下一部\n");
			}

			coor.x = 0, coor.y = 0;
			continue;
		}
		printf("key %d\n",key);
		if(y < 80 && x>720)
		{
			system("killall -9 mplayer");
			break;
		}
		
		if (key == 1)
		{
			write_cmd(fifo_fd, "volume +10");
			printf("音量加10\n");
			key = 0;
		}
		else if (key == 2)
		{
			write_cmd(fifo_fd, "volume -10");
			printf("音量减10\n");
			key = 0;
		}
		else if (key == 4)
		{
			write_cmd(fifo_fd,"seek +20\n");
			printf("快进20秒\n");
			key = 0;
		}
		else if (key == 3)
		{
			write_cmd(fifo_fd,"seek -20\n");
			printf("快退20秒\n");
			key = 0;
		}
		
		
		
	}

}
