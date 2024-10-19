/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialise_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-19 12:25:26 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-19 12:25:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// not implemented
int init_exit(t_game *game)
{
	return (1);
}

int init_coins(t_game *game)
{
	size_t			i;
	t_anim_sprite	*coin;
	t_view_obj		*obj;

	// create a list of images for the frame list
	i = 1;
	obj = create_anim_instance((t_position){0,0}, 3, init_sprite_var(game->mlx, (t_position){1,1}, game->anim_engine, (char *[]){"../../assets/coin.png", 0}));
	if (!obj) // Need to cleanup the image list as well.
		return (anim_destroy_sprite(coin), 0);
	obj->pos = *((t_position *)ft_lstget(game->map->coins, 0)->content);
	view_add_obj(game->view, obj);
	while (i < game->map->coin_count)
	{
		coin = anim_sprite_create(game->anim_engine, create_frame_list((t_list *)((t_anim_sprite *)obj->data)->context, game->mlx), 1);
		if (!coin) // need some function to destory everything
			return (anim_destroy_sprite(coin), 0);
		view_add_obj(game->view, create_anim_instance((t_position){0,0}, 3, coin));
		obj->pos = *((t_position *)ft_lstget(game->map->coins, i)->content);
		i++;
	}
	return (1);
}

// not implemented 
int init_player(t_game *game)
{
	return (1);
}

// not implemented
int init_sprites(t_game *game)
{
	return (1);
}