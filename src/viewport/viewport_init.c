/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 14:05:57 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 14:05:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

// Move somewhere else
t_position min_pos(t_position a, t_position b);

mlx_image_t	*init_background(t_viewport *view, char *path)
{
	mlx_image_t		*image;
	int				**instance_array;
	t_position		size;

	size = min_pos(view->viewport_size, view->map->size);
	image = image_from_path(view->mlx, path);
	if (!image)
		return (0);
	mlx_resize_image(image, view->tile_size[1], view->tile_size[0]);
	instance_array = create_instance_matrix(view->mlx, image,
			size);
	if (instance_array == 0)
		return (free_instance_matrix(instance_array, size),
			mlx_delete_image(view->mlx, image), (void *)0);
	move_matrix(view, image, instance_array, 0);
	free_instance_matrix(instance_array, size);
	view->bg_img = image;
	view->bg_path = path;
	return (image);
}

mlx_image_t	*init_foreground(t_viewport *view, char *path)
{
	mlx_image_t		*image;
	int				**instance_array;
	t_position		size;

	size = min_pos(view->viewport_size, view->map->size);
	image = image_from_path(view->mlx, path);
	if (!image)
		return (0);
	mlx_resize_image(image, view->tile_size[1], view->tile_size[0]);
	instance_array = create_instance_matrix(view->mlx, image,
			size);
	if (instance_array == 0)
		return (free_instance_matrix(instance_array, size),
			mlx_delete_image(view->mlx, image), (void *)0);
	view->fg_matrix = instance_array;
	move_matrix(view, image, instance_array, 1);
	view->fg_img = image;
	view->fg_path = path;
	return (image);
}

t_viewport	*init_viewport(mlx_t *mlx, t_map *map, char *textures[2])
{
	t_viewport *view;

	view = zeroit(malloc(sizeof(t_viewport)), sizeof(t_viewport));
	if (!view)
		return (0);
	view->mlx = mlx;
	view->map = map;
	view->viewport_size = (t_position){VIEWPORT_HEIGHT, VIEWPORT_WIDTH};
	view->tile_size[0] = mlx->height / VIEWPORT_HEIGHT;
	view->tile_size[1] = mlx->width / VIEWPORT_WIDTH;
	if (VIEWPORT_HEIGHT < map->height || VIEWPORT_WIDTH < map->width)
		view->map_smaller = 0;
	else
	{
		view->map_smaller = 1;
		view->map_offset = (t_position){
			((VIEWPORT_HEIGHT - map->height) / 2) * view->tile_size[0],
			((VIEWPORT_WIDTH - map->width) / 2) * view->tile_size[1]};
	}
	if (!init_background(view, textures[0]))
		return (free(view), (void *)0);
	if (!init_foreground(view, textures[1]))
		return (mlx_delete_image(mlx, view->bg_img),
			free(view), (void *)0);
	return (view);
}

void destroy_viewport(t_viewport *view)
{
	mlx_delete_image(view->mlx, view->bg_img);
	mlx_delete_image(view->mlx, view->fg_img);
	free_instance_matrix(view->fg_matrix, view->map->size);
	free(view);
}
