NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH = srcs
SRC		= main.c \
			game_init.c \
			utils.c \
			hook/hook_func.c \
			hook/hook_utils.c \
			map_loader.c \
			validate/map.c \
			validate/content.c \
			validate/wall.c \
			validate/solvable.c \
			draw_map.c \
			mlx_init.c \
			find_elements.c \

OBJ_PATH	= obj
OBJ 		= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH)/, $(OBJ))

INC_PATH = includes
INCS = -I$(INC_PATH) -I$(MLX_PATH)

MLX_PATH = $(HOME)/minilibx-linux
MLX = $(MLX_PATH)/libmlx_Linux.a

LIB_PATH	= libft
LIB			= libft.a
LIBS		= $(addprefix $(LIB_PATH)/, $(LIB))

RM			= rm -f

all: $(LIBS) $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(MLX) $(LIBS) -L$(HOME)/minilibx-linux -lmlx -lXext -lX11 -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBS):
	$(MAKE) -C $(LIB_PATH)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_PATH)
	$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

test:
	@if [ -z "$(MAP)" ]; then \
		valgrind --leak-check=full --show-leak-kinds=all ./so_long maps/map.ber; \
	else \
		valgrind --leak-check=full --show-leak-kinds=all ./so_long maps/$(MAP).ber; \
	fi

.PHONY: all clean fclean re test
