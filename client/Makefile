CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
INCS = -I./inc -I../libs/libmx/inc
LIBS = -L../libs/libmx -lmx

# Folders
SRC=src
OBJ=obj

BINARY = uchat

CFILES = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) \
		 $(wildcard src/*/*/*/*.c) \
		 $(wildcard src/*/*/*/*/*.c)
OBJ_DIR = obj

CONFIG = `pkg-config --libs --cflags gtk+-3.0`

###############################################################################

all: uninstall ${BINARY}

${BINARY}:
	@make -sC ../libs/libmx
	@mkdir -p ${OBJ_DIR}
	@${CC} ${CFLAGS} ${INCS} ${LIBS} ${CFILES} ${CONFIG} -o ${BINARY}

uninstall:
	@rm -rf ${BINARY}
	@make uninstall -sC ../libs/libmx

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -sC ../libs/libmx

reinstall: all

###############################################################################
