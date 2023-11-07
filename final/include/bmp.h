#ifndef __BMP_H_
#define __BMP_H_

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>


struct bitmap_header
{
	int16_t type;
	int32_t size; // ͼ���ļ���С
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits; // bmpͼ������ƫ����
}__attribute__((packed));

struct bitmap_info
{
	int32_t size; // ���ṹ��С	
	int32_t width;
	int32_t height; // ��Ϊ��
	int16_t planes; // ��Ϊ��
	int16_t bit_count; // ɫ��
	int32_t compression;
	int32_t size_img; // bmp���ݴ�С��������4��������
	int32_t X_pel;
	int32_t Y_pel;
	int32_t clrused;
	int32_t clrImportant;
}__attribute__((packed));

struct image_info
{
	int width;
	int height;
};

void bmp2lcd(char* bmpfile, char* FB,int xoffset, int yoffset);
char* load_bmp(const char* bmpfile, struct image_info* imginfo);
void bmpclean(char* FB);

#endif
