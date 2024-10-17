/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 20:05:36 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 20:05:36 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim_engine.h"

void	anim_sprite_update(t_anim_sprite *sprite)
{
	t_frame	*current_frame;
	t_frame	*next_frame;

	if (!sprite->enabled
		|| (sprite->finished && !sprite->loop_enabled))
		return ;
	current_frame = get_current_frame(sprite);
	if (!current_frame)
		return ;
	next_frame = get_frame(sprite, sprite->loop(sprite));
	if (!next_frame)
		return ;
	current_frame->image->instances[current_frame->instance].enabled = 0;
	next_frame->image->instances[next_frame->instance].enabled = 1;
}

void	anim_engine_update(t_anim_engine *engine)
{
	t_list			*this_sprite;
	t_anim_sprite	*sprite;

	if (engine->paused)
		return ;
	this_sprite = engine->sprite_list;
	while (this_sprite)
	{
		sprite = (t_anim_sprite *)this_sprite->content;
		if (sprite->enabled
			&& (!sprite->finished || sprite->loop_enabled)
			&& anim_needs_update(sprite, engine->mlx->delta_time))
			anim_sprite_update(sprite);
		this_sprite = this_sprite->next;
	}
	return ;
}

void	anim_update_hook(void *param)
{
	t_anim_engine	*engine;

	engine = (t_anim_engine *)param;
	anim_engine_update(engine);
}
