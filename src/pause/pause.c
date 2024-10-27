/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 11:25:54 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-26 11:25:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	game_pause_hook(void *param)
{
	t_game		*game;
	static int	pressed;

	game = (t_game *)param;
	if (game->state != GM_PLAY && game->state != GM_PAUSE)
		return ;
	if (!pressed && mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		pressed = 1;
		if (game->state == GM_PAUSE)
			game_pause(game, 0);
		else
			game_pause(game, 1);
	}
	else if (pressed && !mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		pressed = 0;
	if (game->state == GM_PAUSE)
	{
		handle_menu_selection(game);
		handle_choice(game);
	}
}

int	init_pause_menu(t_game *g)
{
	int			i;
	t_paus_mnu	*menu;
	t_position	offs;
	mlx_image_t	*img;

	menu = zeroit(malloc(sizeof(t_paus_mnu)), sizeof(t_paus_mnu));
	if (!menu)
		return (0);
	img = center_txt("Paused", g,
			(t_position){g->mlx->height / 2, g->mlx->width / 2});
	ft_lstadd_back(&menu->cleanup, ft_lstnew(img));
	i = -1;
	offs = (t_position){img->instances[0].y
		+ (img->height * 1.8), g->mlx->width / 2};
	while (++i < 3)
	{
		menu->items[i] = center_txt(
				(char *[3]){"Resume", "Restart", "Exit"}[i], g, offs);
		offs.y += img->height * 1.5;
	}
	menu->selected = 1;
	menu->last_selected = 0;
	g->pause_menu = menu;
	return (1);
}

int	destroy_pause(t_game *g)
{
	t_list	*item;
	t_list	*next;

	item = g->pause_menu->cleanup;
	while (item)
	{
		next = item->next;
		mlx_delete_image(g->mlx, item->content);
		free(item);
		item = next;
	}
	mlx_delete_image(g->mlx, g->pause_menu->items[0]);
	mlx_delete_image(g->mlx, g->pause_menu->items[1]);
	mlx_delete_image(g->mlx, g->pause_menu->items[2]);
	mlx_delete_image(g->mlx, g->pause_menu->selector);
	free(g->pause_menu);
	g->pause_menu = 0;
	return (1);
}

int	game_pause(t_game *game, int status)
{
	if (status)
	{
		if (!init_pause_menu(game))
			return (0);
		game->engine->paused = 1;
		game->state = GM_PAUSE;
		return (1);
	}
	else
	{
		game->state = GM_PLAY;
		game->engine->paused = 0;
		destroy_pause(game);
		return (1);
	}
}
