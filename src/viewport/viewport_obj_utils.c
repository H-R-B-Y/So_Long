/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_obj_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 16:37:55 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 16:37:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

static int	pos_in_view(t_position pos, t_viewprt *view)
{
	if (pos.y < view->offset.y
		|| pos.y > view->offset.y
		+ view->size.y)
		return (0);
	if (pos.x < view->offset.x
		|| pos.x > view->offset.x
		+ view->size.x)
		return (0);
	return (1);
}

int	viewport_draw_objects(t_viewprt *view)
{
	t_list		*index;
	t_view_obj	*obj;

	if (!view)
		return (0);
	index = view->objects;
	while (index)
	{
		obj = (t_view_obj *)index->content;
		if (pos_in_view(obj->pos, view) && obj->enabled)
		{
			if (!obj->enable(obj, view))
				ft_putendl_fd("Failed to enable object", 2);
		}
		else
			if (!obj->disable(obj, view))
				ft_putendl_fd("Failed to disable object", 2);
		index = index->next;
	}
	return (1);
}
