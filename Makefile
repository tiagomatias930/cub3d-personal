# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: binario <binario@student.42.fr>            +#+  +:+         +:+      #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 16:22:24 by binario           #+#    #+#              #
#    Updated: 2025/02/06 17:19:16 by binario          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D.application

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = LIBFT-42
MLX_DIR = mlx_linux
GNL_DIR = gnl
INCLUDES = -I include -I $(LIBFT_DIR)/include -I $(MLX_DIR) -I $(GNL_DIR)

# Arquivos fonte e objetos
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(GNL_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.c, $(SRC)))
OBJ += $(patsubst $(GNL_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter $(GNL_DIR)/%.c, $(SRC)))

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Criar diretório de objetos
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Regra para compilar os objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regra principal
all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

# Limpeza dos objetos
clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

# Limpeza completa
fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

# Recompilação total
re: fclean all

.PHONY: all clean fclean re
