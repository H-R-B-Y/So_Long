/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 15:19:54 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 15:19:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

static void	_fg_enable_loop(t_viewprt *view,
	t_position size)
{
	t_position	iter;
	t_position	pos;

	iter.y = 0;

	while (iter.y < size.y)
	{
		pos.y = iter.y + view->view_offset.y;
		iter.x = 0;
		while (iter.x < size.x)
		{
			pos.x = iter.x + view->view_offset.x;
			if (view->map->map[pos.y][pos.x] == MAP_WALL)
				view->fg_img->instances[view->fg_matrix[iter.y][iter.x]].enabled = 1;
			else
				view->fg_img->instances[view->fg_matrix[iter.y][iter.x]].enabled = 0;
			iter.x++;
		}
		iter.y++;
	}
}

int	draw_viewport(t_viewprt *view)
{
	if (view->need_redraw)
	{
		_fg_enable_loop(view, min_pos(view->viewport_size, view_iterator(view)));
		viewport_draw_objects(view);
		view->need_redraw = 0;
	}
	return (1);
}

int resize_larger(t_viewprt *view)
{
	view->map_smaller = (t_position){
		view->map->size.y < view->viewport_size.y,
		view->map->size.x < view->viewport_size.x};
	view->view_offset = (t_position){
		clamp(view->view_offset.y, 0, view->map->size.y - view->viewport_size.y),
		clamp(view->view_offset.x, 0, view->map->size.x - view->viewport_size.x)};
	if (!init_background(view, view->bg_path))
		return (0);
	if (!init_foreground(view, view->fg_path))
		return (0);
	return (1);
}

int	calc_view_size(t_viewprt *view, t_position size)
{
	if (size.y > view->map->size.y
		|| size.x > view->map->size.x
		|| size.y < 1
		|| size.x < 1)
		return (0);
	free_inst_matrix(view->fg_matrix, min_pos(view->viewport_size, view->map->size));
	view->viewport_size = size;
	view->tile_size = (t_position){view->mlx->height / size.y,
		view->mlx->width / size.x};
	mlx_delete_image(view->mlx, view->bg_img);
	mlx_delete_image(view->mlx, view->fg_img);
	if (!resize_larger(view))
		return (0);
	view->need_redraw = 1;
	draw_viewport(view);
	return (1);
}
