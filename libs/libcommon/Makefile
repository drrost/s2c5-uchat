###############################################################################
#                             Editable options                                #
###############################################################################
NAME = libcommon
SRC_DIR	= src/
OBJ_DIR	= obj/
INC_DIR	= inc/
DIRS = $(notdir $(wildcard $(SRC_DIR)*))

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SRC = $(call rwildcard,$(SRC_DIR),*.c)

OBJ	= $(SRC:src/%.c=$(OBJ_DIR)%.o)
INC_H = $(wildcard $(INC_DIR)*.h)

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic\
	-Wno-unused-command-line-argument -Wno-unused-variable \
	-Wno-unused-function -Wno-unused-parameter -g

LIB_INC = ../libmx/inc

IFLAGS = $(addprefix -I, $(LIB_INC) $(INC_DIR))

COMPILE	= $(CC) $(IFLAGS) $(CFLAGS)
MAKE_M = make -sf Makefile -C
MKDIR = mkdir -p
RM = /bin/rm -rf

###############################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_BIN)
	@$(COMPILE) $(OBJ) -o $(NAME) -c
	@ar -rc $(NAME).a $(OBJ)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H)
	@mkdir -p $(dir $@)
	@$(COMPILE) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME).a

reinstall: uninstall all

.PHONY: all clean uninstall reinstall

###############################################################################
