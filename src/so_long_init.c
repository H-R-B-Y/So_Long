/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-19 12:01:02 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-19 12:01:02 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_game *game)
{
	// REMINDER implement resize
	game->mlx = mlx_init(1920, 1080, "So Long", 0);
	if (!game->mlx)
		return (0);
	game->anim_engine = anim_engine_init(game->mlx);
	if (!game->anim_engine)
		return (0);
	return (1);
}

int	init_game_map(t_game *game, char *map_path)
{
	int fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map = create_map(map_proto_read(fd));
	if (!game->map)
		return (0);
	close(fd);
	game->view = init_viewport(game->mlx, game->map,
		(char *[2]){"assets/fg.png", "assets/bg.png"});
	if (!game->view)
		return (0);
	game->view->need_redraw = 1;
	return (1);
}

int	init_hooks(t_game *game)
{
	int code;
	code = mlx_loop_hook(game->mlx, anim_update_hook, game->anim_engine);
	if (!code)
		return (0);
	code = mlx_loop_hook(game->mlx, draw_viewport_hook, game->view); // need a wrapper for drawing the viewport
	if (!code)
		return (0);
	// Need movement hooks
	return (1);
}



void cleanup_game(t_game *game)
{
	if (game->view)
		destroy_viewport(game->view);
	if (game->anim_engine)
		anim_engine_cleanup(game->anim_engine);
	if (game->map)
		free_map(game->map);
	if (game->coins)
		ft_lstclear(&game->coins, free);
	if (game->cleanup)
		destroy_image_lst(game->mlx, game->cleanup);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
