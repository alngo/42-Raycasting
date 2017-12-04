# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eabgrall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/12 15:27:07 by eabgrall          #+#    #+#              #
#    Updated: 2017/11/29 21:48:46 by alngo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC_PATH = src

LIBFT = ./libft/libft.a

LIBMLX = ./mlx/libmlx.a

SRC_NAME = main.c input.c graphic.c utils.c init.c ft_ray.c ft_sphere.c ft_cam.c

OBJ_PATH = obj

INCLUDE_PATH = -I include

LIB_A = -lft

LIB_MLX = -lmlx

FRAMEWORK = -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all fclean clean re

all: deps $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) -L ./libft $(LIB_A) -L ./mlx $(LIB_MLX) $(FRAMEWORK) $(OBJ) -o $(NAME)

deps:
	make -C libft/
	make -C mlx/


$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -MMD -MP -g -c $^ -o $@

clean:
	make clean -C libft/
	make clean -C mlx/
	$(RM) -r $(OBJ)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) -r $(NAME)

re: fclean all

-include (OBJ:.o=.d)
