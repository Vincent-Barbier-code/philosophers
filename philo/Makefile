NAME = philo
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread
DEPS = $(INCLUDES)philo.h Makefile
INCLUDES = includes/
SRC_DIR = src/
OBJ_DIR = obj/
FT_PRINTF =  -L ./ft_printf -lftprintf

SRC_FILES = $(addprefix $(SRC_DIR), main.c parsing.c fork.c action.c monitoring.c condition.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(DEPS)
	$(MAKE) -C ft_printf/
	gcc $(CFLAGS) $(OBJ) $(FT_PRINTF) -lpthread -D_REENTRANT -o $(NAME)

all : $(NAME)

clean :
	$(MAKE) clean -C ft_printf/
	rm -rf $(OBJ_DIR)

fclean : clean
	$(MAKE) fclean -C ft_printf/
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

