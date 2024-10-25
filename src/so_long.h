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
 * @param coins Holds a list of the view objects for the coins.
 * @param steps number of steps taken.
 * 
 */
typedef struct s_game t_game;

/**
 * @brief Enumeration of game states.
 * 
 * States are:
 * - GM_TITLE: Title screen.
 * - GM_PAUSE: Game is paused.
 * - GM_PLAY: Game is being played.
 * - GM_WON: Game has been won.
 * - GM_END: Game has ended.
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
 * @param dir_frames list of frames for each direction.
 * @param cur_dir current direction of the player.
 * @param mov_delay delay between moves.
 * @param mov_tmr time since last move.
 */
typedef struct s_player t_player;

enum e_game_state
{
	GM_PLAY,
	GM_PAUSE,
	GM_WON,
	GM_END
};

struct s_player
{
	t_position		pos;
	t_list			*dir_frames;
	int				cur_dir;
	double			mov_delay;
	double			mov_tmr;
};

struct s_game
{
	mlx_t			*mlx;
	t_map			*map;
	t_viewprt		*view;
	t_anim_engine	*engine;
	t_player		plyr;
	t_list			*coins;
	size_t			c_count;
	size_t			steps;
	mlx_image_t		*step_img;
	int				exit_open;
	t_view_obj		*exit_obj;
	t_list			*cleanup;
	t_game_state	state;
};




int		init_game(t_game *game, char *str);
int		init_game_map(t_game *game, char *map_path);
int		init_hooks(t_game *game);
void	cleanup_game(t_game *game);



int		init_sprites(t_game *game);
int		init_coins(t_game *game);

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

/**
 * @brief Check if the player can move in the given direction.
 * 
 * Note directions are as follows:
 * - 0: Up / North
 * - 1: Right / East
 * - 2: Down / South
 * - 3: Left / West
 * 
 * @param game game to check.
 * @param direction direction to check.
 * @return 1 if the player can move, 0 if not.
 */
int	valdidate_mov(t_game *game, int direction);

/**
 * @brief Check if the player is on a coin.
 * @param game game to check.
 * @return A list item containin the viewobj 
 * 		of the coin the player is on.
 */
t_list	*player_on_coin(t_game *game);

int		player_on_exit (t_game *g);
int		move_player(t_game *game, int direction);
void	set_player_pos(t_game *game, t_position pos);

/**
 * @brief Handle the key hook for the game.
 */
void	movement_hook(void *game);

/**
 * @brief Initialise an image list from a list of paths.
 * @param game game to initialise the images for.
 * @param paths list of paths to the
 * 		images (null terminate pls)
 * @param size size to resize the images to.
 */
t_list	*init_img_lst(
		t_game *game, char **paths,
		t_position size);

int	enable_exit(t_game *g);

/**
 * @brief Initialize the end screen.
 * @param g game to initialize the end screen for.
 * 
 * This will set the game state to GM_WON and add a new
 * hook to exit the game when the escape key is pressed.
 */
int	init_end_screen(t_game *g);

/**
 * @brief Re-draws the step counter.
 * @param g game to update the step counter for.
 */
void update_step_counter(t_game *g);

#endif