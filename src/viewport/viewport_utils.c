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

static void	_fg_enable_loop(t_viewport *view,
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
int	draw_viewport(t_viewport *view)
{
	if (view->need_redraw)
	{
		if (view->map_smaller)
			_fg_enable_loop(view, view->map->size);
		else
		{
			// OBJ DRAW CODE HERE TO
			_fg_enable_loop(view, (t_position){VIEWPORT_HEIGHT, VIEWPORT_WIDTH});
		}
		view->need_redraw = 0;
	}
	return (1);
}

void	move_view(t_viewport view, t_position direction)
{
	t_position	new_offset;

	new_offset = (t_position){
		clamp(view.view_offset.y + direction.y, 0, view.map->size.y - VIEWPORT_HEIGHT),
		clamp(view.view_offset.x + direction.x, 0, view.map->size.x - VIEWPORT_WIDTH)};
	if (view.map_smaller)
		return ;
	view.view_offset = new_offset;
	view.need_redraw = 1;
	return ;
}

int	calc_view_size(t_viewport *view, t_position size)
{
	size_t	i;
	mlx_image_t *fgbg[2];

	view->viewport_size = size;
	view->tile_size[0] = view->viewport_size.y / size.y;
	view->tile_size[1] = view->viewport_size.x / size.x;
	i = 0;
	fgbg[1] = view->bg_img;
	fgbg[0] = view->fg_img;

	init_background(view, view->bg_path);
	init_foreground(view, view->fg_path);

	mlx_delete_image(view->mlx, fgbg[0]);
	mlx_delete_image(view->mlx, fgbg[1]);

	return (1);
}
