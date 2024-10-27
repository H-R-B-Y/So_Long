
NAME			= dijkstra.a
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0

HEADERS			:= -I ./include

LIBFT_DIR		?= 
LIBFT			= $(LIBFT_DIR)/libft.a

SRCS			= dijkstra.c dijkstra_utils.c
OBJS			= ${SRCS:.c=.o}

PRINT_DELAY		?= 100000

all: $(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $(OBJS)

.c.o:
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

debug: $(NAME)
		ar d $(NAME) dijkstra.o
ifndef COLOURS
		$(CC) $(CFLAGS) -DPRINT_DELAY=$(PRINT_DELAY) -c debug_dijkstra.c $(HEADERS) -o debug_dijkstra.o
else
		$(CC) $(CFLAGS) -DPRINT_DELAY=$(PRINT_DELAY) -DDIJKSTRA_COLOURS="" -c debug_dijkstra.c $(HEADERS) -o debug_dijkstra.o
		$(CC) $(CFLAGS) -c $(COLOURS) $(HEADERS) -o $(COLOURS:.c=.o)
		ar rcs $(NAME) $(COLOURS:.c=.o)
endif
		$(CC) $(CFLAGS) -c debug_print_dijkstra.c $(HEADERS) -o debug_print_dijkstra.o
		ar rcs $(NAME) debug_dijkstra.o debug_print_dijkstra.o

# NOT LIBRARY STUFF:
# To compile the main file, we need to compile libft.a first
# LIBFT_DIR should be set when compiling the main file
# We dont need to compile libft.a when using Dijkstra as a library
main: $(NAME) $(LIBFT)
		$(CC) $(CFLAGS) main.c $(NAME) $(HEADERS) -o main.out

$(LIBFT):
		@$(MAKE) --directory $(LIBFT_DIR) all



clean:
		@rm -rf ./*.o

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, main, debug
