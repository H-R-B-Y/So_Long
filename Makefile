
NAME			:= test
CFLAGS			:= -Wextra -Wall -Werror
LIBMLX			:= ./lib/MLX42

HEADERS			:= -I ./include -I $(LIBMLX)/include
LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl `pkg-config --libs glfw3` -pthread -lm

LIBFT_DIR		= lib/libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRCS			:= 
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

example:		$(OBJS) $(LIBFT)
		
		$(CC) $(CFLAGS) src/example.c $(LIBS) $(HEADERS) -o example.out

clean:
		
		@rm -rf $(OBJS)
		@rm -rf $(LIBMLX)/build

fclean:			clean
		
		@rm -rf $(NAME)

re:				clean all

.PHONY:			all, clean, fclean, re, libmlx