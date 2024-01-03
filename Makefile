# Nombre del ejecutable
NAME = philo

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs

# Listas de archivos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC_FILES))

# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

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

.PHONY: all clean
