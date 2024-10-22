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

static t_list	*init_image_list(t_game *game, char **paths)
{
	t_list		*list;
	mlx_image_t	*img;
	size_t		i;
	mlx_t	*mlx;

	list = 0;
	i = 0;
	mlx = game->mlx;
	while (paths[i])
	{
		img = image_from_path(mlx, paths[i]);
		mlx_resize_image(img, game->view->tile_size.x, game->view->tile_size.y);
		if (!img)
		{
			while (--i)
			{
				mlx_delete_image(mlx, ((mlx_image_t *)ft_lstget(list, i)->content));
				free(ft_lstget(list, i));
			}
			return (0);
		}
		ft_lstadd_back(&list, ft_lstnew(img));
		i++;
	}
	return (list);
}

static t_anim_sprite	**create_anim_objs(t_game *game, t_list *images)
{
	t_anim_sprite	**coins;
	size_t			i;

	if (!game || !images)
		return (0);
	coins = zeroit(malloc(sizeof(t_anim_sprite *) * (game->map->coin_count + 1)),
		sizeof(t_anim_sprite *) * (game->map->coin_count + 1));
	i = 0;
	while (i < game->map->coin_count)
	{
		coins[i] = anim_sprite_create(game->anim_engine, create_frame_list(images, game->mlx), 1);
		if (!coins[i])
		{
			while (--i)
				anim_destroy_sprite(coins[i]);
			free(coins);
			return (0);
		}
		anim_set_pos(coins[i], 0, 0, 3);
		anim_set_loop(coins[i], anim_loop_forward, 1);
		i++;
	}
	return (coins);
}

static void delete_anim_objs(t_anim_sprite **objs)
{
	t_anim_sprite **i;

	i = objs;
	while (*objs)
	{
		anim_destroy_sprite(*objs);
		objs++;
	}
	free(i);
}	

// delete everything if this fails (cleanup)
int	init_coins(t_game *game)
{
	t_list *images;
	t_anim_sprite **coins;
	t_anim_sprite **i;
	t_view_obj *obj;

	images = init_image_list(game, (char *[]){"assets/frame5.png", "assets/frame4.png", 0});
	if (!images)
		return (0);
	coins = create_anim_objs(game, images);
	if (!coins)
		return (destroy_image_lst(game->mlx, images), 0);
	i = coins;
	while (i[0] != 0)
	{
		obj = create_anim_instance((t_position){0,0}, 3, *i);
		if (!obj)
			return (destroy_image_lst(game->mlx, images), 0);
		obj->pos = *((t_position *)ft_lstget(game->map->coins, i - coins)->content);
		view_add_obj(game->view, obj);
		ft_lstadd_back(&game->coins, ft_lstnew(obj));
		(i)++;
	}
	free(coins);
	ft_lstadd_back(&game->cleanup, images);
	return (1);
}
