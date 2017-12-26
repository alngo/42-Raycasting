NAME = wolf3d

SRC_PATH = src

LIBFT = ./libft/libft.a

LIBMLX = ./mlx/libmlx.a

SRC_NAME =	main.c\
		utils.c\
		ray.c\
		line.c\
		line_draw.c\
		movement.c\
		engine/graphic.c\
		engine/input.c\
		init/get_map_block.c\
		init/get_map_info.c\
		init/init.c\

OBJ_PATH = obj

SUB_PATH = /{init,engine}

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
	@mkdir -p $(OBJ_PATH)$(SUB_PATH) 2> /dev/null || true

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
