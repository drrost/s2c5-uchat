NAME = uchat_server
SRC_DIR	= src/
OBJ_DIR	= obj/
INC_DIR	= inc/
DIRS = $(notdir $(wildcard $(SRC_DIR)*))

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SRC = $(call rwildcard,$(SRC_DIR),*.c)

OBJ	= $(SRC:src/%.c=$(OBJ_DIR)%.o)
INC_H = $(wildcard $(INC_DIR)*.h)

LIB_DIR	= ../libs
LIB_LIST = $(notdir $(wildcard $(LIB_DIR)/*))
LIB_DIRS = $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs)/)
LIB_BIN	= $(join $(LIB_DIRS), $(addsuffix .a, $(LIB_LIST)))
LIB_INC	= $(addsuffix $(INC_DIR), $(LIB_DIRS))

CC = clang
GFLAGS = -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic\
	-Wno-unused-command-line-argument -Wno-unused-variable \
	-Wno-unused-function -Wno-unused-parameter -g

CFLAGS = -lsqlite3 -lpthread
IFLAGS = $(addprefix -I, $(LIB_INC) $(INC_DIR))

COMPILE	= $(CC) $(GFLAGS) $(IFLAGS) $(CFLAGS) $(LIB_BIN)
MAKE_M = make -sf Makefile -C
MKDIR = mkdir -p
RM = /bin/rm -rf

###############################################################################

all: $(LIB_LIST) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_BIN)
	@$(COMPILE) $(OBJ) -o $(NAME)

$(LIB_LIST): $(LIB_DIRS)
	@$(MAKE_M) $(LIB_DIR)/$@

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H)
	@mkdir -p $(dir $@)
	@$(COMPILE) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC ../libs/libcommon
	@make clean -sC ../libs/libmx

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)
	@make uninstall -sC ../libs/libcommon
	@make uninstall -sC ../libs/libmx

reinstall: uninstall all

.PHONY: all clean uninstall reinstall

###############################################################################
