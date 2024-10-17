
NAME			= map_parse.a
CFLAGS			:= -Wextra -Wall -Werror

HEADERS			:= -I ./include

ALGO			?= dijkstra

SRCS			= map_parse.c map_validate_internal.c
SRCS			+= map_pathfind_$(ALGO).c
OBJS			= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		@rm -rf ./*.o

fclean: clean
		@rm -rf $(NAME)
		@rm -rf $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re