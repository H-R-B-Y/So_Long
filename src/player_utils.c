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

void	set_player_pos(t_game *game, t_position pos)
{
	t_list		*img;
	mlx_image_t	*img_inst;

	pos = view_map_to_scrn(game->view, pos);
	img = game->plyr.dir_frames;
	while (img)
	{
		img_inst = img->content;
		img_inst->instances[0].x = pos.x;
		img_inst->instances[0].y = pos.y;
		img = img->next;
	}
}

int	move_player(t_game *g, int direction)
{
	t_position	new_pos;

	if (direction < 0 || direction > 3)
		return (0);
	new_pos = g->plyr.pos;
	new_pos.y += (direction == 2) - (direction == 0);
	new_pos.x += (direction == 1) - (direction == 3);
	g->plyr.pos = new_pos;
	return (1);
}

int	valdidate_mov(t_game *game, int direction)
{
	t_position	new_pos;

	if (direction < 0 || direction > 3)
		return (0);
	new_pos = game->plyr.pos;
	if ((!new_pos.x && direction == 3)
		|| (new_pos.x == game->map->width - 1 && direction == 1)
		|| (!new_pos.y && direction == 0)
		|| (new_pos.y == game->map->height - 1 && direction == 2))
		return (0);
	new_pos.y += (direction == 2) - (direction == 0);
	new_pos.x += (direction == 1) - (direction == 3);
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
	pos = game->plyr.pos;
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

int	player_on_exit(t_game *g)
{
	if (!g->exit_open)
		return (0);
	if (g->map->exit.x == g->plyr.pos.x
		&& g->map->exit.y == g->plyr.pos.y)
		return (1);
	return (0);
}
