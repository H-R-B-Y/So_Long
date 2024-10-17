/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_obj_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 16:01:55 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 16:01:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

t_view_obj	*create_viewport_obj(t_position pos,
	void *data,
	t_view_obj_enable enable,
	t_view_obj_disable disable)
{
	t_view_obj	*view_obj;

	if (!data)
		return (0);
	view_obj = malloc(sizeof(t_view_obj));
	if (!view_obj)
		return (0);
	view_obj->pos = pos;
	view_obj->data = data;
	view_obj->enable = enable;
	view_obj->disable = disable;
	view_obj->destroy = free;
	return (view_obj);
}

int	view_add_obj(t_viewport *view, t_view_obj *obj)
{
	if (!view || !obj)
		return (0);
	ft_lstadd_back(&view->objects, ft_lstnew(obj));
	return (1);
}

static void	view_obj_destroy(t_view_obj *obj)
{
	if (obj)
	{
		if (obj->destroy)
			obj->destroy(obj->data);
		free(obj);
	}
}

int	view_del_obj(t_viewport *view, t_view_obj *obj)
{
	t_list *index;
	t_list *prev;

	if (!view || !obj)
		return (0);
	index = view->objects;
	prev = 0;
	while (index)
	{
		if (index->content == obj)
		{
			if (prev)
				prev->next = index->next;
			else
				view->objects = index->next;
			view_obj_destroy(obj);
			free(index);
			return (1);
		}
		prev = index;
		index = index->next;
	}
	return (0);
}
