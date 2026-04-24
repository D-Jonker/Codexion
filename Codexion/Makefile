CC =		cc

CFLAGS = 	-Wall -Werror -Wextra -pthread -I$(HDR_DIR) -g

BIN_DIR = 	./bin

NAME =		codexion.a

EXEC =	codexion

HDR_DIR = 	coders

HEADERS =	$(HDR_DIR)/source.h $(HDR_DIR)/data.h $(HDR_DIR)/dongles.h $(HDR_DIR)/coders.h

SRC_DIR = 	./src

# $(SRC_DIR)/main.c

SRC =		$(SRC_DIR)/codexion.c $(SRC_DIR)/mutex_dongles.c $(SRC_DIR)/stages.c\
			$(SRC_DIR)/thread_monotoring.c $(SRC_DIR)/threads_coders.c \
			$(SRC_DIR)/utility_functions.c

OBJ_DIR = 	./build

OBJ = 		$(SRC:$(SRC_DIR)/%c=$(OBJ_DIR)/%o)

.PHONY: all clean fclean re run debug

all: $(BIN_DIR) $(OBJ_DIR) $(NAME)

$(NAME) : $(OBJ) | $(OBJ_DIR)
	@ ar -rcs $(NAME) $<
	@ mv $(NAME) $(BIN_DIR)
	@ printf "\e[38;5;142m---===---===---===---===---===---===---\n\e[38;5;252m"
	@ printf "\e[38;5;226m\t  Archive:\e[38;5;184m $@\n\e[38;5;252m"
	@ printf "\e[38;5;142m---===---===---===---===---===---===---\n\e[38;5;252m"

$(BIN_DIR) :
	@ mkdir -p $@

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@ printf "\e[38;5;38m  Made .o:\e[38;5;245m $@\n\e[38;5;252m"
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ rm -rf $(OBJ_DIR)
	@ printf "\e[38;5;112m  Cleaned:\e[38;5;70m $(OBJ_DIR)\n\e[38;5;252m"

fclean: clean
	@ rm -rf $(BIN_DIR)
	@ rm -f a.out $(EXEC)
	@ printf "\e[38;5;208m  Removed:\e[38;5;166m $(EXEC)\n\e[38;5;252m"
	@ printf "\e[38;5;196m  Removed:\e[38;5;160m $(BIN_DIR)\n\n\e[38;5;252m"

re: fclean all

run: re $(EXEC)
	@ printf "\e[38;5;33m\n---===---===---= Output =---===---===---\n\n\e[38;5;252m"
	@ if [ -f $(EXEC) ]; then ./$(EXEC); fi
	@ printf "\e[38;5;33m\n\n---===---===---===---===---===---===---\n\e[38;5;252m"
# 	Makefile returns error the ./codexion returns a error

$(EXEC) : $(OBJ) | $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $^ main.c -o $@

debug: re $(EXEC)
	@ gdb $(EXEC)
