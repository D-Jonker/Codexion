CC      =	cc

CFLAGS  = 	-Wall -Werror -Wextra -pthread -I$(ARC_DIR)

NAME    =	codexion

MAIN	=	main.c

# INPUT   =	1 200 60 60 60 3 60 edf

# INPUT   =	1 200 60 60 60 3 60 fifo

# INPUT   =	4 610 200 200 200 3 60 edf

INPUT   =	4 610 200 200 200 3 60 fifo


# INPUT   =	5 755 200 200 200 5 50 edf

# INPUT   =	5 760 200 200 200 5 50 fifo


# INPUT   =	200 850 200 200 200 3 60 edf

# INPUT   =	200 850 200 200 200 3 50 fifo


# INPUT   =	199 860 200 200 200 3 50 edf

# INPUT   =	199 900 200 200 200 3 50 fifo


ARC_DIR = 	./archive

ARCHIVE =	codexion.a

HDR_DIR = 	coders

HEADERS =	$(HDR_DIR)/source.h $(HDR_DIR)/data.h $(HDR_DIR)/dongles.h $(HDR_DIR)/coders.h

SRC_DIR = 	./src

SRC     =	$(SRC_DIR)/codexion.c $(SRC_DIR)/initialise_structs.c\
			$(SRC_DIR)/monotoring.c $(SRC_DIR)/coders.c $(SRC_DIR)/free_for_all.c\
			$(SRC_DIR)/utility.c $(SRC_DIR)/stages.c\
			$(SRC_DIR)/coder_actions_edf.c $(SRC_DIR)/coder_actions_fifo.c

OBJ_DIR = 	./objects

OBJ     = 	$(SRC:$(SRC_DIR)/%c=$(OBJ_DIR)/%o)

all: $(ARC_DIR) $(OBJ_DIR) $(ARCHIVE) $(NAME)
	@ printf "\e[38;5;142m\n---===---===---===---===---===---===---\n\e[38;5;252m"
	@ if [ -f $(ARC_DIR)/$(ARCHIVE) ]; then printf "\e[38;5;226m\t  Archive:\e[38;5;184m $(ARCHIVE)\n\e[38;5;252m"; fi
	@ if [ -f $(NAME) ]; then printf "\e[38;5;226m\t  Binary:\e[38;5;184m  $(NAME)\n\e[38;5;252m"; fi
	@ printf "\e[38;5;142m---===---===---===---===---===---===---\n\n\e[38;5;252m"

$(ARC_DIR) :
	@ mkdir -p $@

$(OBJ_DIR) :
	@ mkdir -p $@

$(ARCHIVE) : $(OBJ)
	@ ar -rcs $(ARCHIVE) $<
	@ mv $(ARCHIVE) $(ARC_DIR)

$(NAME) : $(OBJ) | $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $^ $(MAIN) -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@ printf "\e[38;5;38m  Made .o:\e[38;5;245m $@\n\e[38;5;252m"
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ rm -rf $(OBJ_DIR)
	@ printf "\e[38;5;112m  Cleaned:\e[38;5;70m $(OBJ_DIR)\n\e[38;5;252m"

fclean: clean
	@ rm -rf $(ARC_DIR)
	@ rm -f a.out $(NAME)
	@ printf "\e[38;5;208m  Removed:\e[38;5;166m $(NAME)\n\e[38;5;252m"
	@ printf "\e[38;5;196m  Removed:\e[38;5;160m $(ARC_DIR)\n\n\e[38;5;252m"

re: fclean all

run:
	@ printf "\e[38;5;33m---===---===---= Output =---===---===---\n\n\e[38;5;252m"
	@ if [ -f $(NAME) ]; then ./$(NAME) $(INPUT); else printf "\t    \e[38;5;116mNo binary found\n"; fi
	@ printf "\e[38;5;33m\n---===---===---===----===---===---===---\n\e[38;5;252m"

rerun: re run

memory:
	@ printf "\n\t       \e[38;5;115mValgrind\n\e[38;5;252m\n"
	@ if [ -f $(NAME) ]; then valgrind ./$(NAME) $(INPUT);else printf "\t    \e[38;5;116mNo binary found\n\n"; fi

helgrind:
	@ printf "\n\t       \e[38;5;196mHelgrind\n\e[38;5;252m\n"
	@ if [ -f $(NAME) ]; then valgrind --tool=helgrind ./$(NAME) $(INPUT);else printf "\t    \e[38;5;116mNo binary found\n\n"; fi

.PHONY: all clean fclean re run gdb memory helgrind
