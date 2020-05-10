## Makefile for the OCR

## Compilers vars

CC			= gcc #-fsanitize=address
CPPFLAGS= -MMD `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
CFLAGS  = -Wall -Wextra -Werror -std=c99 -O0 -g3
LDFLAGS =  
LDLIBS	= `pkg-config --libs sdl` `pkg-config --libs gtk+-3.0` -lSDL_image -lm

OBJ	=	${patsubst %.c, %.o, $(shell find . -name "*.c")}
DEP	= ${SRC:.o=.d}

RM = rm -rf

#BINARY = main

.PHONY: all clean

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ}
	$(shell find . -type f -name '*.d' -exec rm {} +)
	${RM} main

-include ${DEP}

#END
