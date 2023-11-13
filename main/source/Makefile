CROSS = arm-linux
CC = $(CROSS)-gcc
AR = $(CROSS)-ar

CFLAGS = -shared -fPIC

all:libbmp.so libtouch.so
	mv $^ ../lib

libbmp.so:bmp.o
	$(CC) $(CFLAGS) -o $@ $^

libtouch.so:touch.o
	$(CC) $(CFLAGS) -o $@ $^