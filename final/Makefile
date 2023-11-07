vpath %.c = source/
vpath %.h = include/

SRCPATH = ./source

SRC = $(wildcard source/*.c)
OBJ = $(SRC:%.c = %.o)
OBJ := $(filter-out entry.o,$(OBJ))

CROSS = arm-linux

CC = $(CROSS)-gcc

CPPFLAGS += -I ./include/

LDFLAGS += -L ./lib/
LDFLAGS += -lpthread
LDFLAGS += -lfont

all:clean entry

entry:entry.c $(OBJ)
	$(MAKE) -C $(SRCPATH)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

$(OBJ):%.o:%.c 
	$(CC) $< -o $@ $(CPPFLAGS) $(LDFLAGS) -c

main:
	@echo $(OBJ)

clean:
	$(RM) $(OBJ) entry .*.SW?