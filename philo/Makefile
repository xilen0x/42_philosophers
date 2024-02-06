# Nombre del ejecutable
NAME = philo

# Directorios
SRC_DIR = src/
SRC_FILES = main.c action.c initialization.c parsing.c philo.c times.c utils.c utils2.c
SRCS += $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = objs/
OBJ_FILES = $(SRCS:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEPS = $(OBJS:.o=.d)

# Compilador y opciones
CC = clang 
CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR) #-fsanitize=address -fsanitize=thread
INC_DIR = include/


# Regla por defecto
all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all


-include $(DEPS)

.PHONY: all clean fclean re 





