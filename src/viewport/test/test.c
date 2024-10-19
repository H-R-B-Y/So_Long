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
	t_viewprt *v = (t_viewprt *)param;

	if (mlx_is_key_down(v->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(v->mlx);
	if (mlx_is_key_down(v->mlx, MLX_KEY_KP_ADD))
		calc_view_size(v, (t_position){v->viewport_size.y+1, v->viewport_size.x+1});
	if (mlx_is_key_down(v->mlx, MLX_KEY_KP_SUBTRACT))
		calc_view_size(v, (t_position){v->viewport_size.y-1, v->viewport_size.x-1});
	if (mlx_is_key_down(v->mlx, MLX_KEY_D))
	{
		((t_view_obj *)v->objects->content)->pos.x++;
	}
	v->need_redraw = 1;
	draw_viewport(v);
	if (!v->map_smaller.x)
	{	
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
	}}
	if (!v->map_smaller.y)
	{
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
	}}
}

	// t_view_obj *obj = create_viewport_obj((t_position){1, 1}, 
	// 	create_obj_instance(mlx, image_from_path(mlx, "../../../assets/frame1.png")),
	// 	enable_instance, disable_instance);
	// obj->destroy = &destroy_obj_instance;
	// view_add_obj(viewport, obj);
	// // disable_instance(obj, viewport);
	// enable_instance(obj, viewport);



int main(void)
{
	mlx_t *mlx = mlx_init(1600, 900, "Viewport Test", false);
	int fd = open("../../../lib/map_parse/test/test_maps/valid2", O_RDONLY);
	t_map *my_map = create_map(map_proto_read(fd));
	close(fd);
	t_viewprt *viewport = init_viewport(mlx, my_map, (char *[]){BG_PNG, FG_PNG});
	viewport->need_redraw = 1;
	draw_viewport(viewport);

	t_anim_engine *eng = anim_engine_init(mlx);
	t_anim_sprite *player = init_sprite_var(mlx,
		viewport->tile_size, eng, 
		(char *[]){"../../../assets/frame1.png",
			"../../../assets/frame2.png",
			"../../../assets/frame3.png",(void *)0});

	t_view_obj *player_obj = create_anim_instance((t_position){1, 1}, 3, player);
	player_obj->pos = (t_position){1, 24};
	player->frame_duration = 0.1;
	view_add_obj(viewport, player_obj);
	// viewport->view_offset = (t_position){0, 1};
	viewport->need_redraw = 1;

	mlx_loop_hook(mlx, ft_hook, viewport);
	mlx_loop_hook(mlx, anim_update_hook, eng);
	mlx_loop(mlx);
	destroy_viewport(viewport);
	free_map(my_map);
	mlx_terminate(mlx);
	return (0);
}
