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
 * - GM_PLAY: Game is being played.
 * - GM_PAUSE: Game is paused.
 * - GM_WON: Game has been won.
 * - GM_END: Game has ended.
 */
typedef enum e_game_state t_game_state;


typedef struct s_paus_mnu t_paus_mnu;

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
	GM_WON
};

struct s_player
{
	t_position		pos;
	t_list			*dir_frames;
	int				cur_dir;
	double			mov_delay;
	double			mov_tmr;
};

struct s_paus_mnu
{
	t_list		*cleanup;
	mlx_image_t	*items[3];
	mlx_image_t	*selector;
	int			selected;
	int			last_selected;
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
	mlx_image_t		*coinint_img;
	int				exit_open;
	t_view_obj		*exit_obj;
	t_list			*cleanup;
	t_paus_mnu		*pause_menu;
	t_game_state	state;
};

/**
 * @brief Initialize the game.
 * @param game game to initialize.
 * @param str path to the map.
 * @return 1 if successful, 0 if not.
 * 
 * This will init the mlx instance and the anim engine.
 */
int		init_game(t_game *game, char *str);


/**
 * @brief Initialize the game map.
 * @param game game to initialize the map for.
 * @param map_path path to the map.
 * @return 1 if successful, 0 if not.
 * 
 * This will create the map and the viewport.
 * Centering the viewport will need to be done manually.
 */
int		init_game_map(t_game *game, char *map_path);

/**
 * @brief Initialize the hooks for the game.
 * @param game game to initialize the hooks for.
 * @return 1 if successful, 0 if not.
 * 
 * The hooks are:
 * - anim_update_hook
 * - draw_viewport_hook
 * - movement_hook
 * - game_pause_hook
 * 
 * Other existing hooks are added during runtime.
 */
int		init_hooks(t_game *game);

/**
 * @brief Cleanup the game.
 * @param game game to cleanup.
 * 
 * This will cleanup the game map, the sprites and the hooks.
 */
void	cleanup_game(t_game *game);


/**
 * @brief Initialize the sprites for the game.
 * @param game game to initialize the sprites for.
 * @return 1 if successful, 0 if not.
 * 
 * This will initialize the player sprite, coins,
 * and the exit animation sprites.
 */
int		init_sprites(t_game *game);

/**
 * @brief Initialize the player sprite.
 * @param game game to initialize the player sprite for.
 * 
 * Called by init_sprites.
 */
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


/**
 * @brief Check if the player is on the exit.
 * @param game game to check.
 * @return 1 if the player is on the exit, 0 if not.
 */
int		player_on_exit (t_game *g);

/**
 * @brief Set the player position.
 * @param game game to set the player position for.
 * @param pos position to set the player to.
 */
int		move_player(t_game *game, int direction);

/**
 * @brief Set the player position.
 * @param game game to set the player position for.
 * @param pos position to set the player to.
 * 
 * Used by move_player.
 */
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
void		update_step_counter(t_game *g);

/**
 * @brief Creates a new text image centered on the position.
 * @param str string to create the image from.
 * @param g game to create the image for.
 * @param pos position to center the image on.
 * @return The created image.
 */
mlx_image_t	*center_txt(char *str, t_game *g, t_position pos);

/**
 * @brief Handle the pause menu.
 */
void	game_pause_hook(void *param);

/**
 * @brief Pause / Unpause the game.
 * @param game game to pause / unpause.
 * @param status 1 to pause, 0 to unpause.
 */
int		game_pause(t_game *game, int status);

/**
 * @brief Handles running code from pause menu selection.
 */
void	handle_choice(t_game *g);

/**
 * @brief Handles moving the selector in the pause menu.
 */
void	handle_menu_selection(t_game *g);

/**
 * @brief Dummy function for use in lstclear.
 */
void	dummy_clr(void *content);

/**
 * @brief Reset the game.
 * @param g game to reset.
 * @return 1 if successful, 0 if not.
 * 
 * This will reset the game, but will not do any memory management!
 */
int		reset_game(t_game *g);

/**
 * @brief Destroy the pause menu
 */
int		destroy_pause(t_game *g);

/**
 * @brief Center the viewport on the given position.
 * @param v viewport to center.
 * @param p position to center on.
 */
void center_viewport(t_viewprt *v, t_position p);

#endif