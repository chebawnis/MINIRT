# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adichou <adichou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 01:30:46 by adichou           #+#    #+#              #
#    Updated: 2025/02/06 06:23:57 by adichou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = fdf

# Répertoires
SRC_DIR = src
MLX_DIR = lib/minilibx-linux

# Fichiers sources et objets
SRC = $(SRC_DIR)/main.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/fill_tab_utils.c \
		$(SRC_DIR)/rotate_functions.c \
		$(SRC_DIR)/r_rotate_functions.c \
		$(SRC_DIR)/move_functions.c \
		$(SRC_DIR)/zoom_functions.c \
		$(SRC_DIR)/display_functions.c \
		$(SRC_DIR)/mlx_hook_functions.c \
		$(SRC_DIR)/draw_line_utils.c \
		$(SRC_DIR)/draw_line_utils_bis.c \
		$(SRC_DIR)/draw_line_functions.c

OBJ = $(SRC:.c=.o)

# Librairies
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -lmlx -lXext -lX11 -lm

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O3

# Règles
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Llib/LIBFT -lft -L$(MLX_DIR) -lmlx_Linux $(MLX_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
