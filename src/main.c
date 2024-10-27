/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-19 11:49:44 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-19 11:49:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	_fail_init(t_game *g, char *reason)
{
	cleanup_game(g);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(reason, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static int	_pre_game(t_game *g, char *path)
{
	if (!init_game_map(g, path))
		return (_fail_init(g, "Failed to initialize game map"));
	if (!init_sprites(g))
		return (_fail_init(g, "Failed to initialize sprites"));
	center_viewport(g->view, g->map->player);
	set_player_pos(g, g->map->player);
	((mlx_image_t *)ft_lstget(g->plyr.dir_frames,
			g->plyr.cur_dir)->content)->enabled = 1;
	if (!init_hooks(g))
		return (_fail_init(g, "Failed to initialize hooks"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (_fail_init(0, "Usage: ./so_long <map_path>"));
	zeroit(&game, sizeof(t_game));
	if (!init_game(&game, argv[1]))
		return (_fail_init(&game, "Failed to initialize game"));
	if (_pre_game(&game, argv[1]))
		return (1);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
