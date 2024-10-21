/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_translate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 09:17:47 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-18 09:17:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

t_position view_map_to_scrn(t_viewprt *view, t_position pos)
{
	if (!view)
		return ((t_position){0, 0});
	if (pos.x > view->map->size.x
		|| pos.y > view->map->size.y)
		return ((t_position){0, 0});
	return ((t_position){
		(((pos.y - view->view_offset.y)
				* view->tile_size.y) + view->map_offset.y),
		(((pos.x - view->view_offset.x)
				* view->tile_size.x) + view->map_offset.x)});
}

t_position view_scrn_to_map(t_viewprt *view, t_position pos)
{
	if (!view)
		return ((t_position){0, 0});
	if (pos.x < view->map_offset.x
		|| pos.y < view->map_offset.y)
		return ((t_position){0, 0});
	return ((t_position){
		.x = ((pos.x - view->map_offset.x)
			/ view->tile_size.x + view->view_offset.x),
		.y = ((pos.y - view->map_offset.y)
			/ view->tile_size.y + view->view_offset.y)});
}

t_position	view_iterator(t_viewprt *view)
{
	return ((t_position){
		(view->viewport_size.y * !view->map_smaller.y)
			+ (view->map->size.y * view->map_smaller.y),
		(view->viewport_size.x * !view->map_smaller.x)
			+ (view->map->size.x * view->map_smaller.x)});
}

void	view_fgbg_state(t_viewprt *view, int index, int state)
{
	if (index < 0 || index > 2 || state < 0 || state > 1)
		return ;
	if (index == 0)
		view->fg_img->enabled = state;
	if (index == 1)
		view->bg_img->enabled = state;
	return ;
}
