/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-21 19:14:22 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-21 19:14:22 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	mv_view_or_plyr(t_game *g, int dir)
{
	if (dir == 0 && g->view->view_offset.y > 0)
	{
		g->view->view_offset.y -= 1;
	}
	else if (dir == 1
		&& (g->view->view_offset.x + g->view->viewport_size.x) < g->map->width)
	{
		g->view->view_offset.x += 1;
	}
	else if (dir == 2 
		&& (g->view->view_offset.y + g->view->viewport_size.y) < g->map->height)
	{
		g->view->view_offset.y += 1;
	}
	else if (dir == 3 && g->view->view_offset.x > 0)
	{
		g->view->view_offset.x -= 1;
	}
	set_player_pos(g, g->player.pos);
	g->view->need_redraw = 1;
}

int		get_direction(mlx_t *mlx)
{
	int	dir;

	dir = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		dir = 0;
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		dir = 1;
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		dir = 2;
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		dir = 3;
	return (dir);
}

void	movement_hook(void *game)
{
	t_game	*g;
	int		dir;

	g = (t_game *)game;
	if (g->player.move_timer < g->player.move_delay)
		g->player.move_timer += g->mlx->delta_time;
	
	else if (g->state == GAME_STATE_PLAYING)
	{
		dir = get_direction(g->mlx);
		if (dir < 0 || !player_valid_movement(g, dir))
			return ;
		move_player(g, dir);
		mv_view_or_plyr(g, dir);
		g->player.move_timer = 0;
	}
}
