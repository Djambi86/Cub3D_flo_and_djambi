# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/27 01:43:43 by dabdulka          #+#    #+#              #
#    Updated: 2026/07/27 01:43:48 by dabdulka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

INCLUDES_DIR	=	includes
LIBFT_DIR		=	$(INCLUDES_DIR)/Libft
MLX_DIR			=	$(INCLUDES_DIR)/mlx

LIBFT	=	$(LIBFT_DIR)/libft.a
MLX		=	$(MLX_DIR)/libmlx.a

SRC		=	src/main.c \
			src/errors.c \
			src/cleanup.c \
			src/parser_read.c \
			src/parser_lines.c \
			src/parser_utils.c \
			src/parser.c \
			src/parser_elements.c \
			src/parser_colors.c \
			src/parser_map.c \
			src/parser_map_check.c \
			src/init.c \
			src/init_player.c \
			src/textures.c \
			src/hooks.c \
			src/move.c \
			src/render.c \
			src/render_utils.c \
			src/raycast.c \
			src/raycast_utils.c

OBJ		=	$(SRC:.c=.o)

HEADER	=	$(INCLUDES_DIR)/cub3D.h

MLX_LIBS	=	-lXext -lX11 -lm -lbsd

INCS	=	-I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX_DIR)/obj $(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Linux.a
	rm -f $(MLX_DIR)/test/Makefile.gen $(MLX_DIR)/test/*.o $(MLX_DIR)/test/mlx-test

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
