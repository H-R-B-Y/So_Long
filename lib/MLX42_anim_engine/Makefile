

NAME			= anim_engine.a
CFLAGS			:= -Wextra -Wall -Werror

HEADERS			:= -I ./include

SRCS			= anim_engine.c anim_sprite.c anim_sprite_utils.c anim_update.c anim_frame_list.c anim_loops.c
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

re: fclean all

.PHONY: all, clean, fclean, re