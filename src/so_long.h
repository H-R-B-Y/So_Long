/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 22:31:26 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 22:31:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef MAP_KEY
#  define MAP_KEY "#0PEC"
#  define MAP_WALL MAP_KEY[0]
#  define MAP_EMPT MAP_KEY[1]
#  define MAP_PLAY MAP_KEY[2]
#  define MAP_EXIT MAP_KEY[3]
#  define MAP_COIN MAP_KEY[4]
# endif

# include "../include/MLX42.h"
# include "../include/libft.h"

# include "../include/dijkstra.h"
# include "../include/dijkstra_debug.h"
# include "../include/map_parse.h"

# include "../include/anim_engine.h"





# include "viewport/viewport.h"
# include "utils/utils.h"

# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_so_long
{
	mlx_t			*mlx;
	t_map			*map;
	t_anim_engine	*engine;

	size_t			player_moves;
	size_t			coin_count;
	t_position		**coins_collected;

	t_position		player;

	t_viewport		*viewport;

	int				(*is_walkable)(t_map *, t_position);
	int				(*is_collectable)(t_map *, t_position);
	int 			(*is_exit)(t_map *, t_position); // check for win condition

	int				paused;
	
}	t_so_long;

/*
I think the best way to go about the viewport would be to have two tiled grids containing the background and the walls
we can then enable/disable the walls as needed to create the viewport effect
a move function can determine weather there is enough space to move the viewport or the player
all coins will be loaded but enabled/disabled when within the viewport, though we need to keep track of the collected coins so as to not re-enable them

if the map is not large enough to fill the viewport then we can just center the map in the viewport


Enemy patrol for bonus can be dealt with in another submodule, this could utilise the pathfinding algorithm to determine the shortest path to the player??? maybe

Displaying the movement count on screen for the bonus should be easy enough.
*/

/*
To Do:
- figure out the best way to draw the map
- figure out the best way to handle the viewport and resizing of the window etc.
- implement the movement of the player
- implement the collection of coins
- implement the win condition and win screen????
- ART
- ensure no leaks
- implement patrol for bonus
- implement movement count for bonus
- add a pause screen
- add a home screen?????
*/

#endif