/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 17:00:10 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 17:00:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

#define BG_PNG "../../../assets/bg.png"
#define FG_PNG "../../../assets/fg.png"

#include "fcntl.h"

void ft_hook(void* param)
{
	t_viewport *v = (t_viewport *)param;

	if (mlx_is_key_down(v->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(v->mlx);
	if (mlx_is_key_down(v->mlx, MLX_KEY_KP_ADD))
		calc_view_size(v, (t_position){v->viewport_size.y+1, v->viewport_size.x+1});
	if (mlx_is_key_down(v->mlx, MLX_KEY_KP_SUBTRACT))
		calc_view_size(v, (t_position){v->viewport_size.y-1, v->viewport_size.x-1});
	if (v->map_smaller)
		return ;
	if (mlx_is_key_down(v->mlx, MLX_KEY_LEFT))
	{
		v->view_offset.x = clamp(v->view_offset.x - 1, 0, v->map->size.x - v->viewport_size.x);
		v->need_redraw = 1;
		draw_viewport(v);
	}
	if (mlx_is_key_down(v->mlx, MLX_KEY_RIGHT))
	{
		v->view_offset.x = clamp(v->view_offset.x + 1, 0, v->map->size.x - v->viewport_size.x);
		v->need_redraw = 1;
		draw_viewport(v);
	}
	if (mlx_is_key_down(v->mlx, MLX_KEY_UP))
	{
		v->view_offset.y = clamp(v->view_offset.y - 1, 0, v->map->size.y - v->viewport_size.y);
		v->need_redraw = 1;
		draw_viewport(v);
	}
	if (mlx_is_key_down(v->mlx, MLX_KEY_DOWN))
	{
		v->view_offset.y = clamp(v->view_offset.y + 1, 0, v->map->size.y - v->viewport_size.y);
		v->need_redraw = 1;
		draw_viewport(v);
	}
	v->need_redraw = 1;
	draw_viewport(v);
}

int main(void)
{
	mlx_t *mlx = mlx_init(1600, 900, "Viewport Test", false);
	int fd = open("../../../lib/map_parse/test/test_maps/valid1", O_RDONLY);
	t_map *my_map = create_map(map_proto_read(fd));
	close(fd);
	t_viewport *viewport = init_viewport(mlx, my_map, (char *[]){BG_PNG, FG_PNG});
	viewport->need_redraw = 1;
	draw_viewport(viewport);

	mlx_loop_hook(mlx, ft_hook, viewport);
	mlx_loop(mlx);
	destroy_viewport(viewport);
	free_map(my_map);
	mlx_terminate(mlx);
	return (0);
}
