# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/23 13:59:22 by kmaneera          #+#    #+#              #
#    Updated: 2020/08/18 16:56:52 by kmaneera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 2Dto3D

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -framework OpenGL -framework AppKit
INC = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) -I$(MINILIBX_HEADERS)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)includes/

MINILIBX = $(MINILIBX_DIR)libmlx.a
MINILIBX_DIR = ./minilibx/
MINILIBX_HEADERS = $(MINILIBX_DIR)

HEADERS_LIST = cub3d.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRCS_DIR = ./sources/
SRCS_LIST = main.c map1.c map2.c map3.c map4.c map5.c\
			engine.c bg.c rc.c lst.c 3d.c minimap.c\
			minimap_util.c texture.c move.c rotate.c util.c\
			sprite.c sprite_util.c sprite_lst.c bmp.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJ_DIR = objects/
OBJ_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIBS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INC) $< -o $@

$(LIBFT):
	#@$(MAKE) -sC $(LIBFT_DIR)

$(MINILIBX):
	#@$(MAKE) -sC $(MINILIBX_DIR)

clean:
	#@$(MAKE) -sC $(MINILIBX_DIR) clean
	#@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	#@rm -f $(MINILIBX)
	#@rm -f $(LIBFT)
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all