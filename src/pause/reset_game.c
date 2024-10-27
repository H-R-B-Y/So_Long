/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 13:49:39 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-26 13:49:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void reset_coins(t_game *g)
{
	t_list		*tmp;
	t_view_obj	*coin;

	tmp = g->coins;
	while (tmp)
	{
		coin = (t_view_obj *)tmp->content;
		coin->enabled = 1;
		coin->enable(coin, g->view);
		anim_set_state((t_anim_sprite *)coin->data, 1);
		tmp = tmp->next;
	}
}

static void	reset_exit(t_game *g)
{
	t_view_obj		*exit_obj;
	t_anim_sprite	*exit_sprite;
	t_frame			*frame;

	exit_obj = g->exit_obj;
	exit_sprite = (t_anim_sprite *)exit_obj->data;
	exit_sprite->finished = 1;
	exit_sprite->loop_enabled = 0;
	exit_sprite->current_frame = 0;
	anim_set_state(exit_sprite, 0);
	frame = get_frame(exit_sprite, 0);
	frame->image->instances[frame->instance].enabled = 1;
	frame = get_frame(exit_sprite, 1);
	frame->image->instances[frame->instance].enabled = 0;
}

int	reset_game(t_game *g)
{
	if (g->pause_menu)
		destroy_pause(g);
	g->steps = 0;
	g->plyr.pos = g->map->player;
	g->state = GM_PLAY;
	g->c_count = 0;
	g->exit_open = 0;
	reset_coins(g);
	center_viewport(g->view, g->map->player);
	set_player_pos(g, g->plyr.pos);
	g->view->need_redraw = 1;
	reset_exit(g);
	g->engine->paused = 0;
	return (1);
}
