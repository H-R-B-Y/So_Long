
NAME			= so_long.out
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 -fsanitize=address
#CFLAGS			:= -g3 -O0 -fsanitize=address

HEADERS			:= -I ./include

LIB_DIR			:= ./lib

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

SRC_DIR			:= ./src
SRCS			:= $(SRC_DIR)/so_long_init.c \
				$(SRC_DIR)/viewport/instance_matrix.c \
				$(SRC_DIR)/viewport/viewport_init.c \
				$(SRC_DIR)/viewport/viewport_obj_init.c \
				$(SRC_DIR)/viewport/viewport_obj_utils.c \
				$(SRC_DIR)/viewport/viewport_translate.c \
				$(SRC_DIR)/viewport/viewport_utils.c \
				$(SRC_DIR)/utils/clamp.c \
				$(SRC_DIR)/utils/image_from_path.c \
				$(SRC_DIR)/utils/min_max_pos.c \
				$(SRC_DIR)/utils/set_instance_pos.c \
				$(SRC_DIR)/utils/destroy_image_lst.c \
				$(SRC_DIR)/utils/image_lst.c \
				$(SRC_DIR)/viewport/view_obj_anim_obj/sprite_init_wrapper.c \
				$(SRC_DIR)/viewport/view_obj_anim_obj/view_obj_anim.c \
				$(SRC_DIR)/viewport/view_ob_mlx_inst/viewport_obj_inst.c \
				$(SRC_DIR)/init_sprites/init_sprites.c \
				$(SRC_DIR)/init_sprites/init_coins.c \
				$(SRC_DIR)/init_sprites/init_exit.c \
				$(SRC_DIR)/player_utils.c \
				$(SRC_DIR)/movement_hook.c \
				$(SRC_DIR)/endscreen.c \
				$(SRC_DIR)/step_counter.c


OBJS			:= ${SRCS:.c=.o}

PRINT_DELAY		?= 100000

MAIN 			:= $(SRC_DIR)/main.c

all: $(NAME)

$(LIBFT):
		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

$(MAP_PARSE):
		$(MAKE) --directory $(MAP_PARSE_DIR) all CFLAGS="$(CFLAGS)"

$(DIJKSTRA):
		$(MAKE) --directory $(DIJKSTRA_DIR) all CFLAGS="$(CFLAGS)" $(DEBUG) PRINT_DELAY=$(PRINT_DELAY)

$(ANIM_ENGINE):
		$(MAKE) --directory $(ANIM_ENGINE_DIR) all CFLAGS="$(CFLAGS)"

$(LIBMLX):
		cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make CFLAGS="$(CFLAGS)" -C $(LIBMLX_DIR)/build -j4 

$(NAME): $(MAIN) $(OBJS) $(LIBFT) $(ANIM_ENGINE) $(LIBMLX) $(DIJKSTRA) $(MAP_PARSE)
		$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(ANIM_ENGINE) $(MAP_PARSE) $(DIJKSTRA) $(LIBFT) $(LIBMLX) $(LIBFLAGS) -o $(NAME)

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		$(MAKE) --directory $(LIBFT_DIR) clean
		$(MAKE) --directory $(ANIM_ENGINE_DIR) clean
		$(MAKE) --directory $(MAP_PARSE_DIR) clean
		$(MAKE) --directory $(DIJKSTRA_DIR) clean
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(LIBMLX_DIR)/build
		$(MAKE) --directory $(LIBFT_DIR) fclean
		$(MAKE) --directory $(ANIM_ENGINE_DIR) fclean
		$(MAKE) --directory $(MAP_PARSE_DIR) fclean
		$(MAKE) --directory $(DIJKSTRA_DIR) fclean
		rm -rf $(NAME)

rm:
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, test
