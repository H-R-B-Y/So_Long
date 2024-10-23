/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-21 18:52:48 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-21 18:52:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_player_pos(t_game *game, t_position pos)
{
	t_list		*img;
	mlx_image_t	*img_inst;
	
	pos = view_map_to_scrn(game->view, pos);
	img = game->player.dir_frames;
	while (img)
	{
		img_inst = img->content;
		img_inst->instances[0].x = pos.x;
		img_inst->instances[0].y = pos.y;
		img = img->next;
	}
}

int	move_player(t_game *game, int direction)
{
	t_position	new_pos;
	t_list		*img;
	mlx_image_t	*img_inst;
	int			i;

	if (direction < 0 || direction > 3)
		return (0);
	new_pos = game->player.pos;
	new_pos.y += (direction == 2) - (direction == 0);
	new_pos.x += (direction == 1) - (direction == 3);
	game->player.pos = new_pos;
	img = game->player.dir_frames;
	i = 0;
	set_player_pos(game, new_pos);
	return (1);
}

int	player_valid_movement(t_game *game, int direction)
{
	t_position	new_pos;

	if (direction < 0 || direction > 3)
		return (0);
	new_pos = game->player.pos;
	new_pos.y += (direction == 2) - (direction == 0);
	new_pos.x += (direction == 1) - (direction == 3);
	if (new_pos.x < 0 || new_pos.y < 0
		|| new_pos.x >= game->map->size.x
		|| new_pos.y >= game->map->size.y)
		return (0);
	if (game->map->map[new_pos.y][new_pos.x] == MAP_WALL)
		return (0);
	return (1);
}

t_list	*player_on_coin(t_game *game)
{
	t_list		*coins;
	t_position	coin;
	t_position	pos;
	int			i;

	coins = game->coins;
	pos = game->player.pos;
	i = 0;
	while (coins)
	{
		if (coins->content)
		{
		coin = ((t_view_obj *)coins->content)->pos;
		if (((t_anim_sprite *)((t_view_obj *)coins->content)->data)
			->enabled
			&& coin.x == pos.x && coin.y == pos.y)
			return (coins);
		coins = coins->next;
		}
		i++;
	}
	return (0);
}
