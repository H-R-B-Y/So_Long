
CFLAGS			:= -Wextra -Wall -Werror

HEADERS			:= -I $(LIBMLX)/include -I ../

LIB_DIR			:= ../../../lib

LIBFT_DIR		= $(abspath $(LIB_DIR)/libft)
LIBFT			= $(LIBFT_DIR)/libft.a

DIJKSTRA_DIR	= $(abspath $(LIB_DIR)/dijkstra)
DIJKSTRA 		= $(DIJKSTRA_DIR)/dijkstra.a

DEBUG			:=
PRINT_DELAY		:= 100000

select:
		@echo "Select a target to compile: test_map_validate"
		@echo "Use DEBUG=debug to compile with debug flags"
		@echo "Can set print delay with PRINT_DELAY=<delay>"

# Tests here

test_map_validate.out: $(LIBFT) $(DIJKSTRA)
		$(CC) $(CFLAGS) -c ../map_parse.c ../map_pathfind_dijkstra.c ../map_validate_internal.c $(HEADERS)
		$(CC) $(CFLAGS) test_map_validate.c map_parse.o map_pathfind_dijkstra.o map_validate_internal.o $(DIJKSTRA) $(LIBFT) $(HEADERS) -o test_map_validate.out


# Other stuff here

$(DIJKSTRA):
		@echo "Compiling dijkstra"
		$(MAKE) --directory $(DIJKSTRA_DIR) all $(DEBUG) PRINT_DELAY=$(PRINT_DELAY) LIBFT_DIR=$(LIBFT_DIR) LIBFT=$(LIBFT)

$(LIBFT):
		@echo "Compiling libft"
		$(MAKE) --directory $(LIBFT_DIR) all

dummy:
		@echo $(LIBFT)
		@echo $(DIJKSTRA)


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

.PHONY:			all, clean, fclean, re, select