
NAME			:= test
CFLAGS			:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX			:= ./lib/MLX42

HEADERS			:= -I ./include -I $(LIBMLX)/include
LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT_DIR		= lib/libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRCS			:= src/main.c
OBJS			:= ${SRCS:.c=.o}


all:			libmlx $(LIBFT) $(NAME)

$(LIBFT):
		
		$(MAKE) --directory $(LIBFT_DIR)

libmlx:
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
		
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME):		$(OBJS) $(LIBFT) 
		
		@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
		
		@rm -rf $(OBJS)
		@rm -rf $(LIBMLX)/build

fclean:			clean
		
		@rm -rf $(NAME)

re:				clean all

.PHONY:			all, clean, fclean, re, libmlx