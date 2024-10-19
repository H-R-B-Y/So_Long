/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_obj_anim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 09:04:57 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-18 09:04:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view_obj_anim.h"

int enable_anim_instance(t_view_obj *obj, t_viewprt *view)
{
	t_anim_sprite	*data;
	t_position		pos;

	if (!obj || !view)
		return (0);
	data = (t_anim_sprite *)obj->data;
	if (!data || !data->frame_list)
		return (0);
	pos = view_map_to_scrn(view, obj->pos);
	anim_set_pos(data, pos.x, pos.y, obj->depth);
	anim_set_state(data, 1);
	return (1);
}

int disable_anim_instance(t_view_obj *obj, t_viewprt *view)
{
	t_anim_sprite	*data;

	if (!obj || !view)
		return (0);
	data = (t_anim_sprite *)obj->data;
	if (!data || !data->frame_list)
		return (0);
	anim_set_state(data, 0);
	return (1);
}

void destroy_anim_instance(void *data, t_viewprt *view)
{
	t_anim_sprite	*sprite;
	t_list			*img_list;

	if (!data || !view)
		return ;
	sprite = (t_anim_sprite *)data;
	if (sprite->context)
	{
		img_list = (t_list *)sprite->context;
		while (img_list)
		{
			if (img_list->content)
				mlx_delete_image(view->mlx, (mlx_image_t *)img_list->content);
			img_list = img_list->next;
		}
		ft_lstclear((t_list **)&sprite->context, free);
	}
	anim_destroy_sprite(sprite);
}
