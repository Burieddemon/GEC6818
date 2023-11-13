#include "bmp.h"
#include "touch.h"


void bmp2lcd(char* bmpfile, char* FB, int xoffset, int yoffset)
{
	struct image_info imginfo;
	char* bmp_fp = load_bmp(bmpfile, &imginfo);
	for (int y = 0; y < imginfo.height && y + yoffset < HEIGHT; ++y)
	{
		for (int x = 0; x < imginfo.width && x + xoffset < WIDTH; ++x)
		{
			memcpy(FB + (xoffset + x) *4  + (y + yoffset) * 800*4 , bmp_fp + y * imginfo.width * 3 + x * 3, 3);
		}
	}
	free(bmp_fp);
}
char* load_bmp(const char* bmpfile, struct image_info* imginfo)
{
	int bmp_fd = open(bmpfile, O_RDONLY);
	if (-1 == bmp_fd)
	{
		printf("open %s failed:%s", bmpfile, strerror(errno));
		exit(0);
	}
	struct stat filestat;
	fstat(bmp_fd, &filestat);
	int size = filestat.st_size;

	char* buf = (char*)malloc(size * 4);
	struct bitmap_header bitheader;
	struct bitmap_info bitinfo;
	read(bmp_fd, &bitheader, sizeof(struct bitmap_header));
	read(bmp_fd, &bitinfo, sizeof(struct bitmap_info));
	imginfo->height = bitinfo.height;
	imginfo->width = bitinfo.width;
	int w = bitinfo.width;
	int h = bitinfo.height;

	int rub = w * 3 % 4 ? (4 - w * 3 % 4) : 0;
	for (int i = 0; i < h; i++)
	{
		read(bmp_fd, buf + w * 3 * i, w * 3);
		lseek(bmp_fd, rub, SEEK_CUR);
	}

	char* rev_buf = (char*)malloc(size * 4);
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			memcpy(rev_buf + i * 3 + j * w * 3, buf + i * 3 + (h - j - 1) * w * 3, 3);
		}
	}
	
	return rev_buf;	 
}
void bmpclean(char* FB)
{
	int color = 0x00000000;
	for (int i = 0; i < 800*480*4; i++)
	{
		memcpy(FB+i, &color, 4);
	}
}