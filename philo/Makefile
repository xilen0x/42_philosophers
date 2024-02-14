# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: castorga <castorga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:39:38 by castorga          #+#    #+#              #
#    Updated: 2024/02/14 13:27:25 by castorga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src/
SRC_FILES = main.c action.c initialization.c parsing.c philo.c times.c utils.c \
			utils2.c action2.c
SRCS += $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = objs/
OBJ_FILES = $(SRCS:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEPS = $(OBJS:.o=.d)

CC = clang 
CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR) -fsanitize=address
#CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR) -fsanitize=thread
#CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR)

INC_DIR = include/

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





