/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anime_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 19:40:49 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 19:40:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim_engine.h"

t_anim_sprite	*anim_sprite_create(t_anim_engine *engine,
	t_frame_list frame_list,
	double frame_duration)
{
	t_anim_sprite	*sprite;

	sprite = zeroit(malloc(sizeof(t_anim_sprite)), sizeof(t_anim_sprite));
	if (!sprite)
		return (0);
	sprite->frame_list = frame_list;
	sprite->frame_count = ft_lstsize(frame_list);
	if (!sprite->frame_count)
	{
		destroy_frame_list(frame_list);
		free(sprite);
		return (0);
	}
	sprite->frame_duration = frame_duration;
	sprite->enabled = 0;
	ft_lstadd_back(&engine->sprite_list, ft_lstnew(sprite));
	return (sprite);
}

void	anim_destroy_sprite(t_anim_sprite *sprite)
{
	destroy_frame_list(sprite->frame_list);
	free(sprite);
}

void	anim_set_loop(t_anim_sprite *sprite, t_loop_type loop, short loop_enabled)
{
	sprite->loop = loop;
	sprite->loop_enabled = loop_enabled;
}

void	anim_set_pos(t_anim_sprite *sprite, int x, int y, int z)
{
	t_frame_list	frame;
	t_frame			*frame_content;

	sprite->x = x;
	sprite->y = y;
	sprite->z = z;
	frame = sprite->frame_list;
	while (frame)
	{
		frame_content = (t_frame *)frame->content;
		frame_content->image->instances[frame_content->instance].x = x;
		frame_content->image->instances[frame_content->instance].y = y;
		mlx_set_instance_depth(
			&(frame_content->image->instances[frame_content->instance]),
			z);
		frame = frame->next;
	}
}

int	anim_set_state(t_anim_sprite *sprite, short enabled)
{
	t_frame	*frame;

	if (enabled)
	{
		if (!sprite->loop
			|| !sprite->frame_list
			|| !sprite->frame_count
			|| sprite->frame_duration < 0)
			return (0);
		sprite->enabled = 1;
		frame = get_current_frame(sprite);
		if (!frame)
			return (0);
		frame->image->instances[frame->instance].enabled = 1;
	}
	else
	{
		frame = get_current_frame(sprite);
		if (!frame)
			return (0);
		frame->image->instances[frame->instance].enabled = 0;
		sprite->enabled = 0;
	}
	return (1);
}
