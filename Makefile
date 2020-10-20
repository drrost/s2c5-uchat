###############################################################################
#                             Editable options                                #
###############################################################################
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
INCS = -I./inc -I./libmx/inc
LIBS = -L./libmx/ -lmx

# Folders
SRC=src
OBJ=obj

BINARY = ush

CFILES = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) \
		 $(wildcard src/*/*/*/*.c) \
		 $(wildcard src/*/*/*/*/*.c)
OBJ_DIR = obj

###############################################################################

all: uninstall ${BINARY}

${BINARY}:
	@make -sC libmx
	@mkdir -p ${OBJ_DIR}
	@${CC} ${CFLAGS} ${INCS} ${LIBS} ${CFILES} -o ${BINARY}

uninstall:
	@rm -rf ${BINARY}
	@make uninstall -sC libmx

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -sC libmx

reinstall: all

###############################################################################
