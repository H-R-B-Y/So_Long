
NAME			= test.out
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 -fsanitize=address

HEADERS			:= -I ./include

LIB_DIR			:= ../../../lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

ANIM_ENGINE_DIR	:= $(abspath $(LIB_DIR)/MLX42_anim_engine)
ANIM_ENGINE		:= $(ANIM_ENGINE_DIR)/anim_engine.a

LIBMLX_DIR		:= $(abspath $(LIB_DIR)/MLX42)
LIBMLX			:= $(LIBMLX_DIR)/build/libmlx42.a -ldl `pkg-config --libs glfw3` -pthread -lm

SRCS 			:= 
OBJS			:= ${SRCS:.c=.o}

all: $(NAME)

test: $(NAME)

$(LIBFT):
		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

$(ANIM_ENGINE):
		$(MAKE) --directory $(ANIM_ENGINE_DIR) all CFLAGS="$(CFLAGS)"

libmlx:
		@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(NAME): $(OBJS) $(LIBFT) $(ANIM_ENGINE) libmlx
		$(CC) $(CFLAGS) test.c $(OBJS) $(ANIM_ENGINE) $(LIBFT) $(LIBMLX) -o $(NAME)

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		$(MAKE) --directory $(LIBFT_DIR) clean
		$(MAKE) --directory $(ANIM_ENGINE_DIR) clean
		rm -rf $(LIBMLX_DIR)/build
		@rm -rf ./*.o

fclean: clean
		$(MAKE) --directory $(LIBFT_DIR) fclean
		$(MAKE) --directory $(ANIM_ENGINE_DIR) fclean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, test
