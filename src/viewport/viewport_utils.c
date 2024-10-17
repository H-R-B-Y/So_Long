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

t_position min_pos(t_position a, t_position b);

static void	_fg_enable_loop(t_viewport *view,
	t_position size)
{
	t_position	iter;
	t_position	pos;

	iter.y = 0;
	size = min_pos(view->viewport_size, view->map->size);
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
int	draw_viewport(t_viewport *view)
{
	if (view->need_redraw)
	{
		if (view->map_smaller)
			_fg_enable_loop(view, min_pos(view->viewport_size, view->map->size));
		else
		{
			// OBJ DRAW CODE HERE TO
			_fg_enable_loop(view, min_pos(view->viewport_size, view->map->size));
		}
		view->need_redraw = 0;
	}
	return (1);
}

void	move_view(t_viewport *view, t_position direction)
{
	t_position	new_offset;

	new_offset = (t_position){
		clamp(view->view_offset.y + direction.y, 0, view->map->size.y - view->viewport_size.y),
		clamp(view->view_offset.x + direction.x, 0, view->map->size.x - view->viewport_size.x)};
	if (view->map_smaller)
		return ;
	view->view_offset = new_offset;
	view->need_redraw = 1;
	return ;
}

int resize_larger(t_viewport *view)
{
	view->map_smaller = 0;
	view->view_offset = (t_position){
		clamp(view->view_offset.y, 0, view->map->size.y - view->viewport_size.y),
		clamp(view->view_offset.x, 0, view->map->size.x - view->viewport_size.x)};
	if (!init_background(view, view->bg_path))
		return (0);
	if (!init_foreground(view, view->fg_path))
		return (0);
	return (1);
}

int	calc_view_size(t_viewport *view, t_position size)
{
	mlx_image_t *fgbg[2];

	if (size.y < 1
		|| size.x < 1)
		return (0);
	if (size.y > view->map->size.y
		|| size.x > view->map->size.x)
		return (0);
	free_instance_matrix(view->fg_matrix, min_pos(view->viewport_size, view->map->size));
	view->viewport_size = size;
	view->tile_size[0] = view->mlx->height / size.y;
	view->tile_size[1] = view->mlx->width / size.x;
	fgbg[1] = view->bg_img;
	fgbg[0] = view->fg_img;

	if (!resize_larger(view))
		return (0);
	mlx_delete_image(view->mlx, fgbg[0]);
	mlx_delete_image(view->mlx, fgbg[1]);
	view->need_redraw = 1;
	draw_viewport(view);
	return (1);
}
