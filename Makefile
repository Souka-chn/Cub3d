NAME = cub3D

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror  -I. -I$(LIBFT_DIR) #-fsanitize=address -g3 -fsanitize=leak

SRCS = main.c \
       parsing/parser.c \
       parsing/map_valid.c \
       parsing/color_parser.c \
       parsing/validation.c \
       parsing/handle_identifiers.c \
       parsing/utils.c \
       parsing/map_parser.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c \
       execution/texture_loader.c \
       execution/raycasting.c \
       execution/raycasting_utils.c \
       execution/renderer.c \
       execution/renderer_utils.c \
       execution/controls.c \
       execution/minimap.c \
       execution/minimap_utils_1.c \
       execution/minimap_utils_2.c \
       execution/movement.c \
       execution/initialisation.c \
       execution/doors.c \
       execution/doors_utils_1.c \
       execution/doors_utils_2.c \
       execution/sprite_animation.c \
       execution/sprite_utils_1.c \
       execution/sprite_utils_2.c \
       execution/sprite_parser.c \
       execution/collision.c


OBJS = $(SRCS:.c=.o)


all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)  -L minilibix-linux -lmlx -lX11 -lXext -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@make -C Libft clean
	rm -f $(OBJS)

fclean: clean
	@make -C Libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
