#include "game.h"

void Game_Init(int data[line][line])
{
	printf("init:%d\n", __LINE__);
	bmpclean(p);
	bmp2lcd("res/game/background.bmp", p, 0, 0);
	Init_Font();
	Clean_Area(480, 0, 319, 479, 0xFFFFFFFF);
	srand((unsigned)time(NULL));
	getRand(data);
	getRand(data);
	showimg(data);
}


void showimg(int data[line][line])
{
	int x, y;
	for (int x = 0; x < line; x++)
	{
		for (int y = 0; y < line; y++)
		{
			if (data[x][y] == 0)
			{
				usleep(10);
				bmp2lcd("res/game/item.bmp", p, 19 + 115 * x, 19 + 115 * y);
			}
			else
			{
				usleep(10);
				switch (data[x][y])
				{
				case 2: bmp2lcd("res/game/block_2.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 4: bmp2lcd("res/game/block_4.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 8: bmp2lcd("res/game/block_8.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 16: bmp2lcd("res/game/block_16.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 32: bmp2lcd("res/game/block_32.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 64: bmp2lcd("res/game/block_64.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 128: bmp2lcd("res/game/block_128.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 256: bmp2lcd("res/game/block_256.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 512: bmp2lcd("res/game/block_512.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 1024: bmp2lcd("res/game/block_1024.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				case 2048: bmp2lcd("res/game/block_2048.bmp", p, 19 + 115 * x, 19 + 115 * y); break;
				}
			}
		}
	}
}

void getRand(int data[line][line])
{
	printf("getRand:%d\n", __LINE__);
	int x, y;
	int nood;
	while (1)
	{
		x = rand() % line;
		y = rand() % line;

		if (data[x][y] != 0)
			continue;
		data[x][y] = 2;
		break;
	}
}

void moveLift(int data[line][line])
{
	printf("宸n");
	int x = 0, y = 0;
	int isChange = 0;

	for (x = 0; x < line; x++)
	{
		for (y = 0; y < line - 1; y++)
		{
			if (data[y][x] == 0)
				continue;
			for (int i = y + 1; i < line; i++)
			{
				printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);
				if (data[i][x] == 0)
					continue;
				else if (data[i][x] != data[y][x])
					break;
				else
				{
					data[y][x] += data[i][x];
					data[i][x] = 0;
					isChange = 1;
					printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);
					break;
				}
			}
		}
	}

	for (x = 0; x < line; x++)
	{
		for (y = 0; y < line; y++)
		{
			printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);
			if (data[y][x] == 0)
				continue;
			int i = y - 1;
			while (data[i][x] == 0 && i >= 0)
			{
				i--;
			}
			if (data[i + 1][x] == 0)
			{
				data[i + 1][x] = data[y][x];
				data[y][x] = 0;
				isChange = 1;
			}
			printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);

		}
	}
	if (isChange)
	{
		getRand(data);
	}
}

void moveRight(int data[line][line])
{
	printf("鍙砛n");
	int x = 0, y = 0;
	int isChange = 0;
	for (x = 0; x < line; x++)
	{
		for (y = line - 1; y > 0; y--)
		{
			if (data[y][x] == 0)
				continue;
			for (int i = y - 1; i >= 0; i--)
			{
				if (data[i][x] == 0)
					continue;
				else if (data[i][x] != data[y][x])
					break;
				else
				{
					data[y][x] += data[i][x];
					data[i][x] = 0;
					isChange = 1;
					printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);
					break;
				}
			}
		}
	}
	for (x = 0; x < line; x++)
	{
		for (y = line - 2; y >= 0; y--)
		{
			if (data[y][x] == 0)
				continue;
			int i = y + 1;
			while (data[i][x] == 0 && i < line)
			{
				i++;
			}
			if (data[i - 1][x] == 0)
			{
				data[i - 1][x] = data[y][x];
				data[y][x] = 0;
				isChange = 1;
			}
		}
	}
	if (isChange)
	{
		getRand(data);
	}
}

void moveUp(int data[line][line])
{
	printf("涓奬n");
	int x = 0, y = 0;
	int isChange = 0;
	for (x = 0; x < line; x++)
	{
		for (y = 0; y < line - 1; y++)
		{
			if (data[x][y] == 0)
				continue;
			for (int i = y + 1; i < line; i++)
			{
				if (data[x][i] == 0)
					continue;
				else if (data[x][i] != data[x][y])
					break;
				else
				{
					data[x][y] += data[x][i];
					data[x][i] = 0;
					isChange = 1;
					printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);
					break;
				}
			}
		}
	}
	for (x = 0; x < line; x++)
	{
		for (y = 1; y < line; y++)
		{
			if (data[x][y] == 0)
				continue;
			int i = y - 1;
			while (data[x][i] == 0 && i >= 0)
			{
				i--;
			}
			if (data[x][i + 1] == 0)
			{
				data[x][i + 1] = data[x][y];
				data[x][y] = 0;
				isChange = 1;
			}
		}
	}
	if (isChange)
	{
		getRand(data);
	}

}

void moveDown(int data[line][line])
{
	printf("涓媆n");
	int x = 0, y = 0;
	int isChange = 0;
	for (x = 0; x < line; x++)
	{
		for (y = line - 1; y > 0; y--)
		{
			if (data[x][y] == 0)
				continue;
			for (int i = y - 1; i >= 0; i--)
			{
				if (data[x][i] == 0)
					continue;
				else if (data[x][i] != data[x][y])
					break;
				else
				{
					data[x][y] += data[x][i];
					data[x][i] = 0;
					isChange = 1;
					printf("x:%d,y:%d,data:%d\n", x, y, data[x][y]);
					break;
				}
			}
		}
	}
	for (x = 0; x < line; x++)
	{
		for (y = line - 2; y >= 0; y--)
		{
			if (data[x][y] == 0)
				continue;
			int i = y + 1;
			while (data[x][i] == 0 && i < line)
			{
				i++;
			}
			if (data[x][i - 1] == 0)
			{
				data[x][i - 1] = data[x][y];
				data[x][y] = 0;
				isChange = 1;
			}
		}
	}
	if (isChange)
	{
		getRand(data);
	}
}

int isGameOver(int data[line][line])
{

	for (int x = 0; x < line; x++)
	{
		for (int y = 0; y < line; y++)
		{
			if (data[x][y] == 0)
				return 0;
		}
	}
	for (int x = 0; x < line - 1; x++)
	{
		for (int y = 0; y < line; y++)
		{
			if (data[x][y] == data[x + 1][y])
				return 0;
		}
	}
	for (int x = 0; x < line; x++)
	{
		for (int y = 0; y < line - 1; y++)
		{
			if (data[x][y] == data[x][y + 1])
				return 0;
		}
	}
	return 1;
}

int getScore(int data[line][line])
{
	int score = 0;
	for (int x = 0; x < line; x++)
	{
		for (int y = 0; y < line; y++)
		{
			if (score < data[x][y])
			{
				score = data[x][y];
			}
		}
	}
	return score;
}

int maxSroce(int data)
{
	int fd = open("res/game/maxvalue.txt", O_RDWR);
	if (fd == -1)
	{
		perror("open txt failed:");
		exit(1);
	}
	char buf[20] = "\0";
	read(fd, buf, sizeof(buf) / sizeof(buf[0]));
	int maxValue = 0;
	sscanf(buf, "最高分 : %d", &maxValue);
	if (maxValue < data);
	{
		sprintf(buf, "最高分 : %d", data);
		write(fd, buf, sizeof(buf) / sizeof(buf[0]));
	}
	close(fd);
	return maxValue;
}

void game()
{

	int data[line][line] = { 0 };
	int loser = 0;
	int flag = 1;
	int maxValue = maxSroce(data[0][0]);
	int score = 0;
	Game_Init(data);
	printf("main:%d\n", __LINE__);
	char score_buf[1024] = "\0";
	sprintf(score_buf, "最高分 :%d", maxValue);
	Display_characterX(480, 50, score_buf, 0x00000000,2);
	while (1)
	{
		usleep(100);
		sprintf(score_buf, "得  分:%d", score);
		Display_characterX(480, 100, score_buf, 0x00000000,2);
		switch (key)
		{			
		case 1: moveUp(data);		break;
		case 2: moveDown(data);		break;
		case 3: moveLift(data);		break;
		case 4: moveRight(data);	break;		
		default:
			if (coor.x <80 && coor.y <80)
			{
				coor.x = 0,coor.y = 0;
				
				flag = 0;
				break;
			}
			continue;
		}
		if(flag == 0)
		{
			break;
		}
		showimg(data);
		loser = isGameOver(data);
		score = getScore(data);
		if (loser)
		{
			bmp2lcd("res/game/gameover.bmp", p, 0, 0);
			sleep(2);
			Game_Init(data);
			if (score > maxValue)
			{
				maxSroce(score);
			}
			loser = 0;
			score = 0;
		}
		
		
		key = 0;
		Clean_Area(480, 100, 200, 479, 0xFFFFFFFF);
	}
	UnInit_Font();
}
