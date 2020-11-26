NAME = uchat

###############################################################################

all: $(LIB_LIST) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_BIN)
	@make -sC ./client
	@make -sC ./server

clean:
	@make clean -sC ./client
	@make clean -sC ./server

uninstall:
	@make uninstall -sC ./client
	@make uninstall -sC ./server

reinstall: uninstall all

.PHONY: all clean uninstall reinstall

###############################################################################
