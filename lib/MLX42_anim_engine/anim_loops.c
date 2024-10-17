/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 19:30:49 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 19:30:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim_engine.h"

size_t	anim_loop_forward(t_anim_sprite *sprite)
{
	if (sprite->current_frame + 1 < sprite->frame_count)
		sprite->current_frame++;
	else if (sprite->loop_enabled)
		sprite->current_frame = 0;
	else
		sprite->finished = 1;
	return (sprite->current_frame);
}

size_t	anim_loop_backward(t_anim_sprite *sprite)
{
	if (sprite->current_frame > 0)
		sprite->current_frame--;
	else if (sprite->loop_enabled)
		sprite->current_frame = sprite->frame_count - 1;
	else
		sprite->finished = 1;
	return (sprite->current_frame);
}

size_t	anim_loop_pingpong(t_anim_sprite *sprite)
{
	if (!sprite->finished)
	{
		if (sprite->current_frame + 1 < sprite->frame_count)
			sprite->current_frame++;
		else
		{
			sprite->current_frame--;
			sprite->finished = 1;
		}
	}
	else
	{
		if (sprite->current_frame > 0)
			sprite->current_frame--;
		else
		{
			sprite->finished = 0;
			sprite->current_frame++;
		}
	}
	return (sprite->current_frame);
}
