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


static int	player_centered(t_game *g)
{
	t_position	pos;
	int			x;
	int			y;

	pos = g->player.pos;
	x = (g->map->width - g->view->viewport_size.x) / 2;
	y = (g->map->height - g->view->viewport_size.y) / 2;
	if (x + g->view->viewport_size.x > pos.x || x < pos.x
		|| y + g->view->viewport_size.y > pos.y || y > pos.y)
		return (0);
	return (1);
}

static void	mv_view_or_plyr(t_game *g, int dir)
{
	if (!player_centered(g))
	{
		if (dir == 0 && g->view->view_offset.y > 0)
			g->view->view_offset.y -= 1;
		else if (dir == 1
			&& (g->view->view_offset.x + g->view->viewport_size.x) < g->map->width)
			g->view->view_offset.x += 1;
		else if (dir == 2 
			&& (g->view->view_offset.y + g->view->viewport_size.y) < g->map->height)
			g->view->view_offset.y += 1;
		else if (dir == 3 && g->view->view_offset.x > 0)
			g->view->view_offset.x -= 1;
	}
	set_player_pos(g, g->player.pos);
	g->view->need_redraw = 1;
}

static int	get_direction(mlx_t *mlx)
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

static int	remove_coin(t_game *g, t_view_obj *coin)
{
	t_list	*sprite;

	if (!coin)
		return (0);
	coin->enabled = 0;
	coin->disable(coin, g->view);
	return (1);
}

// 607000040520

void	movement_hook(void *game)
{
	t_game	*g;
	int		dir;
	t_list	*coin;

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
		g->steps++;
		coin = player_on_coin(g);
		if (coin)
			g->coins_collected += remove_coin(g, coin->content);
		if ((g->coins_collected)
			== g->map->coin_count
			&& !g->exit_open)
			enable_exit(g);
		g->player.move_timer = 0;
	}
}
