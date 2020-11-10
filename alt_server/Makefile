CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
INCS = -I./inc -I../libs/libmx/inc -I../libs/libcommon/inc
LIBS = -L../libs/libmx -lmx -L../libs/libcommon -lcommon

# Folders
SRC=src
OBJ=obj

BINARY = uchat_server

CFILES = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) \
		 $(wildcard src/*/*/*/*.c) \
		 $(wildcard src/*/*/*/*/*.c) \
		 $(wildcard src/*/*/*/*/*/*.c)
OBJ_DIR = obj

CONFIG = `pkg-config --libs --cflags gtk+-3.0`

###############################################################################

all: uninstall ${BINARY}

${BINARY}:
	@make -sC ../libs/libcommon
	@make -sC ../libs/libmx
	@mkdir -p ${OBJ_DIR}
	@${CC} ${CFLAGS} ${INCS} ${LIBS} ${CFILES} ${CONFIG} -o ${BINARY}

uninstall:
	@rm -rf ${BINARY}
	@make uninstall -sC ../libs/libcommon
	@make uninstall -sC ../libs/libmx

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -sC ../libs/libcommon
	@make clean -sC ../libs/libmx

reinstall: all

###############################################################################
