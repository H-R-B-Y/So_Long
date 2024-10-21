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
# include "viewport/view_ob_mlx_inst/viewport_obj_inst.h"
# include "viewport/view_obj_anim_obj/view_obj_anim.h"
# include "utils/utils.h"

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


/**
 * @brief Structure to hold the game state.
 * @param mlx MLX42 instance.
 * @param map map to display.
 * @param view viewport to display the map.
 * @param anim_engine animation engine.
 * @param player_pos position of the player.
 * @param coins The coins that have been collected.
 * @param steps number of steps taken.
 * 
 */
typedef struct s_game t_game;

/**
 * @brief Enumeration of game states.
 * 
 * States are:
 * - GAME_STATE_TITLE: Title screen.
 * - GAME_STATE_PAUSED: Game is paused.
 * - GAME_STATE_PLAYING: Game is being played.
 * - GAME_STATE_WON: Game has been won.
 * - GAME_STATE_END: Game has ended.
 */
typedef enum e_game_state t_game_state;

/**
 * @brief Structure to hold the player.
 * 
 * Note that directions are as follows:
 * - 0: Up / North
 * - 1: Right / East
 * - 2: Down / South
 * - 3: Left / West
 * Direction frames are stored in order.
 * 
 * @param pos position of the player.
 * @param direction_frames list of frames for each direction.
 * @param current_direction current direction of the player.
 */
typedef struct s_player t_player;

enum e_game_state
{
	GAME_STATE_TITLE,
	GAME_STATE_PAUSED,
	GAME_STATE_PLAYING,
	GAME_STATE_WON,
	GAME_STATE_END
};

struct s_player
{
	t_position	pos;
	t_list		*direction_frames;
	int			current_direction;
};

struct s_game
{
	mlx_t			*mlx;
	t_map			*map;
	t_viewprt		*view;
	t_anim_engine	*anim_engine;
	t_player		player;
	t_list			*coins;
	size_t			steps;
	t_list			*cleanup;
	t_game_state	state;
};




int		init_game(t_game *game);
int		init_game_map(t_game *game, char *map_path);
int		init_hooks(t_game *game);
void	cleanup_game(t_game *game);



int		init_sprites(t_game *game);


/**
 * @brief Move the player in the given direction.
 * 
 * Does not check for walls!!!
 * 
 * Note directions are as follows:
 * - 0: Up / North
 * - 1: Right / East
 * - 2: Down / South
 * - 3: Left / West
 * 
 * @param game game to move the player in.
 * @param direction direction to move the player in.
 */
int		move_player(t_game *game, int direction);


#endif