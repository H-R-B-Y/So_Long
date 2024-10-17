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

static int	pos_in_view(t_position pos, t_viewport *view)
{
	if (pos.y < view->view_offset.y
		|| pos.y >= view->view_offset.y + view->viewport_size.y)
		return (0);
	if (pos.x < view->view_offset.x
		|| pos.x >= view->view_offset.x + view->viewport_size.x)
		return (0);
	return (1);
}

int	viewport_draw_objects(t_viewport *view)
{
	t_list	*index;
	t_view_obj	*obj;

	if (!view)
		return (0);
	index = view->objects;
	while (index)
	{
		obj = (t_view_obj *)index->content;
		if (pos_in_view(obj->pos, view))
			obj->enable(obj, view);
		else
			obj->disable(obj, view);
		index = index->next;
	}
	return (1);
}
