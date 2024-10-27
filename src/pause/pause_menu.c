/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 12:14:06 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-26 12:14:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	enable_disable(t_paus_mnu *p, t_game *g, int i)
{
	(void)i;
	if (!p->selector)
		p->selector = mlx_put_string(g->mlx, ">", 0, 0);
	if (p->selected != p->last_selected)
	{
		p->selector->instances[0].x = p->items[p->selected - 1]
			->instances[0].x - p->selector->width;
		p->selector->instances[0].y = p->items[p->selected - 1]
			->instances[0].y;
		p->last_selected = p->selected;
	}
}

void	handle_menu_selection(t_game *g)
{
	static int	pressed;

	if (mlx_is_key_down(g->mlx, MLX_KEY_DOWN) && !pressed)
	{
		pressed = 1;
		g->pause_menu->selected++;
		if (g->pause_menu->selected > 3)
			g->pause_menu->selected = 1;
	}
	else if (mlx_is_key_down(g->mlx, MLX_KEY_UP) && !pressed)
	{
		pressed = 1;
		g->pause_menu->selected--;
		if (g->pause_menu->selected < 1)
			g->pause_menu->selected = 3;
	}
	else if (!mlx_is_key_down(g->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(g->mlx, MLX_KEY_UP))
		pressed = 0;
	enable_disable(g->pause_menu, g, 0);
}

void	handle_choice(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_ENTER))
	{
		if (g->pause_menu->selected == 1)
			game_pause(g, 0);
		else if (g->pause_menu->selected == 2)
			reset_game(g);
		else if (g->pause_menu->selected == 3)
			mlx_close_window(g->mlx);
	}
}
