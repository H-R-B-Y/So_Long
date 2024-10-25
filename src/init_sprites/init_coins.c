/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-21 16:02:50 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-21 16:02:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_anim_sprite	**create_anim_objs(
		t_game *game, t_list *images)
{
	t_anim_sprite	**coins;
	size_t			i;

	if (!game || !images)
		return (0);
	coins = zeroit(malloc(sizeof(t_anim_sprite *)
		* (game->map->coin_count + 1)),
		sizeof(t_anim_sprite *) * (game->map->coin_count + 1));
	i = 0;
	while (i < game->map->coin_count)
	{
		coins[i] = anim_sprite_create(game->engine,
			create_frame_list(images, game->mlx), 1);
		if (!coins[i])
		{
			while (--i)
				anim_destroy_sprite(coins[i]);
			return (free(coins), (void *)0);
		}
		anim_set_pos(coins[i], 0, 0, 3);
		anim_set_loop(coins[i], anim_loop_forward, 1);
		coins[i]->frame_duration = 0.5;
		i++;
	}
	return (coins);
}	

// delete everything if this fails (cleanup)
int	init_coins(t_game *g)
{
	t_list *images;
	t_anim_sprite **coins;
	t_anim_sprite **i;
	t_view_obj *obj;

	images = init_img_lst(g, (char *[])
		{"assets/frame5.png", "assets/frame4.png", 0},
		g->view->tile_size);
	coins = create_anim_objs(g, images);
	if (!coins)
		return (destroy_image_lst(g->mlx, images), 0);
	i = coins;
	while (i[0] != 0)
	{
		obj = create_anim_instance((t_position){0,0}, 3, *i);
		if (!obj)
			return (destroy_image_lst(g->mlx, images), 0);
		obj->pos = 
			*((t_position *)ft_lstget(
				g->map->coins, i++ - coins)->content);
		view_add_obj(g->view, obj);
		ft_lstadd_back(&g->coins, ft_lstnew(obj));
	}
	ft_lstadd_back(&g->cleanup, images);
	return (free(coins), 1);
}
