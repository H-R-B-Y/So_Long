NAME			= test.out
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 -fsanitize=address

HEADERS			:= -I ./include

LIB_DIR			:= /home/herb/42work/so_long/lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

ANIM_ENGINE_DIR	:= $(abspath $(LIB_DIR)/MLX42_anim_engine)
ANIM_ENGINE		:= $(ANIM_ENGINE_DIR)/anim_engine.a

DIJKSTRA_DIR	:= $(abspath $(LIB_DIR)/dijkstra)
DIJKSTRA		:= $(DIJKSTRA_DIR)/dijkstra.a

MAP_PARSE_DIR	:= $(abspath $(LIB_DIR)/map_parse)
MAP_PARSE		:= $(MAP_PARSE_DIR)/map_parse.a

LIBMLX_DIR		:= $(abspath $(LIB_DIR)/MLX42)
LIBMLX			:= $(LIBMLX_DIR)/build/libmlx42.a
LIBFLAGS		:=  -ldl `pkg-config --libs glfw3` -pthread -lm

SRCS 			:= ../instance_matrix.c ../viewport_init.c ../viewport_utils.c ../../utils/image_from_path.c ../../utils/set_instance_pos.c ../../utils/clamp.c
OBJS			:= ${SRCS:.c=.o}

all: $(NAME)

test: $(NAME)

$(LIBFT):
		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

$(MAP_PARSE):
		$(MAKE) --directory $(MAP_PARSE_DIR) all CFLAGS="$(CFLAGS)"

$(DIJKSTRA):
		$(MAKE) --directory $(DIJKSTRA_DIR) all CFLAGS="$(CFLAGS)"

$(ANIM_ENGINE):
		$(MAKE) --directory $(ANIM_ENGINE_DIR) all CFLAGS="$(CFLAGS)"

$(LIBMLX):
		cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(NAME): test.c $(OBJS) $(LIBFT) $(ANIM_ENGINE) $(LIBMLX) $(DIJKSTRA) $(MAP_PARSE)
		$(CC) $(CFLAGS) test.c $(OBJS) $(ANIM_ENGINE) $(MAP_PARSE) $(DIJKSTRA) $(LIBFT) $(LIBMLX) $(LIBFLAGS) -o $(NAME)

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		$(MAKE) --directory $(LIBFT_DIR) clean
		$(MAKE) --directory $(ANIM_ENGINE_DIR) clean
		$(MAKE) --directory $(MAP_PARSE_DIR) clean
		$(MAKE) --directory $(DIJKSTRA_DIR) clean
		rm -rf $(LIBMLX_DIR)/build
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) --directory $(LIBFT_DIR) fclean
		$(MAKE) --directory $(ANIM_ENGINE_DIR) fclean
		$(MAKE) --directory $(MAP_PARSE_DIR) fclean
		$(MAKE) --directory $(DIJKSTRA_DIR) fclean
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, test