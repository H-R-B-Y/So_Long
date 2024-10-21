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



int main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long [map.ber]\n", 2);
		return (1);
	}
	// Initialize the game with mlx instance, and anim engine
	zeroit(&game, sizeof(t_game));
	init_game(&game);
	// Parse map and initialize the viewport
	if (!init_game_map(&game, argv[1]))
	{
		cleanup_game(&game);
		ft_putstr_fd("Error\nFailed to parse map\n", 2);
		return (1);
	}
	// Initialize the hooks
	init_sprites(&game);
	if (!init_hooks(&game))
	{
		cleanup_game(&game);
		ft_putstr_fd("Error\nFailed to initialize hooks\n", 2);
		return (1);
	}
	// Start the game loop
	mlx_loop(game.mlx);
	// Destroy the game
	cleanup_game(&game);
	return (0);
}
