NAME = philo
CFLAGS = #-Wall -Wextra -Werror
DEPS = $(INCLUDES)philo.h Makefile
INCLUDES = includes/
SRC_DIR = src/
OBJ_DIR = obj/
FT_PRINTF =  -L ./ft_printf -lftprintf

SRC_FILES = $(addprefix $(SRC_DIR), main.c parsing.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(DEPS)
	gcc $(CFLAGS) $(OBJ) $(FT_PRINTF) -lpthread -D_REENTRANT -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

