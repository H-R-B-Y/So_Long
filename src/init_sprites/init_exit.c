/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-22 09:28:09 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-22 09:28:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	enable_exit(t_game *g)
{
	t_view_obj	*exit_obj;

	exit_obj = g->exit_obj;
	if (!exit_obj)
		return (0);
	((t_anim_sprite *)exit_obj->data)->finished = 0;
	anim_set_state(exit_obj->data, 1);
	g->exit_open = 1;
	return (1);
}

int	init_exit(t_game *g)
{
	t_list			*images;
	t_anim_sprite	*exit_sprite;

	images = init_img_lst(g,
			(char *[]){"assets/exit.png", "assets/exit2.png", 0},
			g->view->tile_size);
	if (!images)
		return (0);
	exit_sprite = anim_sprite_create(g->engine,
			create_frame_list(images, g->mlx), 0.5);
	if (!exit_sprite)
		return (destroy_image_lst(g->mlx, images), 0);
	anim_set_pos(exit_sprite, 0, 0, 3);
	anim_set_loop(exit_sprite, anim_loop_forward, 0);
	exit_sprite->finished = 1;
	g->exit_obj = create_anim_instance(
			g->map->exit, 3, exit_sprite);
	if (!g->exit_obj)
		return (destroy_image_lst(g->mlx, images), 0);
	view_add_obj(g->view, g->exit_obj);
	ft_lstadd_back(&g->cleanup, images);
	return (1);
}
