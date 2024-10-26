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

static void	mv_view_or_plyr(t_game *g, int dir)
{
	size_t	pov_x;
	size_t	pov_y;

	pov_x = g->plyr.pos.x - g->view->offset.x;
	pov_y = g->plyr.pos.y - g->view->offset.y;
	if (dir == 0 && pov_y < g->view->size.y / 2)
		g->view->offset.y -= 1 * (g->view->offset.y > 0);
	else if (dir == 1 && pov_x > g->view->size.x / 2)
		g->view->offset.x += 1 * (
				(g->view->offset.x + g->view->size.x)
				< g->map->width);
	else if (dir == 2 && pov_y > g->view->size.y / 2)
		g->view->offset.y += 1 * (
				(g->view->offset.y + g->view->size.y)
				< g->map->height);
	else if (dir == 3 && pov_x < g->view->size.x / 2)
		g->view->offset.x -= 1 * (g->view->offset.x > 0);
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

static int	del_coin(t_game *g, t_list *coin)
{
	t_view_obj	*coin_obj;

	if (!coin)
		return (0);
	coin_obj = coin->content;
	coin_obj->enabled = 0;
	coin_obj->disable(coin_obj, g->view);
	return (1);
}

static int	handle_movement(t_game *g)
{
	int		dir;
	t_list	*coin;

	dir = get_direction(g->mlx);
	if (dir < 0 || !valdidate_mov(g, dir))
		return (0);
	++g->steps;
	update_step_counter(g);
	move_player(g, dir);
	mv_view_or_plyr(g, dir);
	set_player_pos(g, g->plyr.pos);
	g->view->need_redraw = 1;
	coin = player_on_coin(g);
	g->c_count += del_coin(g, coin) * (!!coin);
	if ((g->c_count) == g->map->coin_count
		&& !g->exit_open)
		enable_exit(g);
	g->plyr.mov_tmr = 0;
	return (1);
}

void	movement_hook(void *game)
{
	t_game	*g;

	g = (t_game *)game;
	g->plyr.mov_tmr += g->mlx->delta_time
		* (g->plyr.mov_tmr < g->plyr.mov_delay);
	if (g->state == GM_PLAY && g->plyr.mov_tmr >= g->plyr.mov_delay)
	{
		handle_movement(g);
		if (player_on_exit(g))
			init_end_screen(g);
	}
}
