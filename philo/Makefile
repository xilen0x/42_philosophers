# Nombre del ejecutable
NAME = philo

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs

# Listas de archivos (*********************CAMBIAR ESTA PARTE POR Q LA NORMA NO LO PERMITE!!!!!!!!!!!!!!!!!)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC_FILES))

# Compilador y opciones
CC = clang -g
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

# Regla por defecto
all: $(NAME)

# Regla para el ejecutable
$(NAME): $(OBJ_FILES)
	$(CC) $^ -o $@

# Regla para los archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Dependencias
-include $(DEP_FILES)

# Reglas para limpieza
clean:
	@rm -rf $(OBJ_DIR) $(NAME)

fclean:clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean
