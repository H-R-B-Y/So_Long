

CFLAGS			:= -Wextra -Wall -Werror -g3 -O0
LIBMLX			:= ../../../lib/MLX42

HEADERS			:= -I $(LIBMLX)/include -I ../

LIBFT_DIR		= ../../../lib/libft
LIBFT			= $(LIBFT_DIR)/libft.a

DIJKSTRA_DIR	= ../dijkstra
DIJKSTRA 		= $(DIJKSTRA_DIR)/dijkstra.a

LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl `pkg-config --libs glfw3` -pthread -lm

DEBUG			:=

select:
		@echo "Select a target to compile: test_map_validate"


# Tests here

test_map_validate: libmlx $(LIBFT) $(DIJKSTRA)
		$(CC) $(CFLAGS) -c ../map_parse_internal.c ../map_pathfind_dijkstra.c ../map_validate_internal.c $(HEADERS)
		$(CC) $(CFLAGS) test_map_validate.c map_parse_internal.o map_pathfind_dijkstra.o map_validate_internal.o $(DIJKSTRA) $(LIBFT) $(LIBS) $(HEADERS) -o test_map_validate.out


# Other stuff here

$(DIJKSTRA):
		@echo "Compiling dijkstra"
		$(MAKE) --directory $(DIJKSTRA_DIR) all $(DEBUG)

$(LIBFT):
		@echo "Compiling libft"
		$(MAKE) --directory $(LIBFT_DIR) all bonus

libmlx:
		
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Clean up

clean:
		@$(MAKE) --directory $(DIJKSTRA_DIR) clean
		@$(MAKE) --directory $(LIBFT_DIR) clean
		@rm -rf $(LIBMLX)/build
		@rm -rf ./*.o

fclean:			clean
		
		@$(MAKE) --directory $(DIJKSTRA_DIR) fclean
		@rm -rf $(LIBFT)
		@rm -rf ./*.out

re:				clean all

.PHONY:			all, clean, fclean, re, libmlx