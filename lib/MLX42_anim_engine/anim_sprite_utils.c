/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 20:06:11 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 20:06:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim_engine.h"

int	anim_needs_update(t_anim_sprite *sprite, double delta_time)
{
	sprite->frame_timer += delta_time;
	if (sprite->frame_timer >= sprite->frame_duration)
	{
		sprite->frame_timer = sprite->frame_timer
			- sprite->frame_duration;
		return (1);
	}
	return (0);
}

t_frame	*get_frame(t_anim_sprite *sprite, size_t index)
{
	t_list	*frame;

	frame = ft_lstget(sprite->frame_list, index);
	if (!frame)
		return (0);
	return ((t_frame *)frame->content);
}

inline t_frame	*get_current_frame(t_anim_sprite *sprite)
{
	return (get_frame(sprite, sprite->current_frame));
}
