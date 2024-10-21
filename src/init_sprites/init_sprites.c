/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialise_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-19 12:25:26 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-19 12:25:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	init_coins(t_game *game);

// not implemented
int init_exit(t_game *game)
{
	return (1);
}

void destroy_player_images(mlx_t *mlx, mlx_image_t *img[4])
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (!img[i] && i++)
			continue ;
		mlx_delete_image(mlx, img[i++]);
	}
}

// not implemented 
int init_player(t_game *game)
{
	mlx_image_t	*img[4];
	int i;
	
	img[0] = image_from_path(game->mlx, "assets/frame1.png");
	img[1] = image_from_path(game->mlx, "assets/frame2.png");
	img[2] = image_from_path(game->mlx, "assets/frame3.png");
	img[3] = image_from_path(game->mlx, "assets/frame4.png");
	if (!img[0] || !img[1] || !img[2] || !img[3])
		return (destroy_player_images(game->mlx, img), 0);
	mlx_image_to_window(game->mlx, img[0], 0, 0);
	mlx_image_to_window(game->mlx, img[1], 0, 0);
	mlx_image_to_window(game->mlx, img[2], 0, 0);
	mlx_image_to_window(game->mlx, img[3], 0, 0);
	game->player.pos = game->map->player;
	i = 0;
	while (i < 4)
	{
		ft_lstadd_back(&game->player.direction_frames, ft_lstnew(img[i]));
		img[i]->enabled = 0;
		i++;
	}
	game->player.current_direction = 0;
	return (1);
}

// not implemented
int init_sprites(t_game *game)
{
	if (!init_coins(game))
		return (0);
	if (!init_player(game))
		return (0);
	ft_lstadd_back(&game->cleanup, game->player.direction_frames);
	if (!init_exit(game))
		return (0);
	return (1);
}
