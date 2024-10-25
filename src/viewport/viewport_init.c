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

mlx_image_t	*init_background(t_viewprt *view, char *path)
{
	mlx_image_t		*image;
	int				**instance_array;
	t_position		size;


	image = image_from_path(view->mlx, path);
	if (!image)
		return (0);
	size = view_iterator(view);
	mlx_resize_image(image, view->tile_size.x, view->tile_size.y);
	instance_array = create_inst_matrix(view->mlx, image,
			size);
	if (instance_array == 0)
		return (free_inst_matrix(instance_array, size),
			mlx_delete_image(view->mlx, image), (void *)0);
	move_matrix(view, image, instance_array, 0);
	free_inst_matrix(instance_array, size);
	view->bg_img = image;
	view->bg_path = path;
	return (image);
}

mlx_image_t	*init_foreground(t_viewprt *view, char *path)
{
	mlx_image_t		*image;
	int				**instance_array;
	t_position		size;


	image = image_from_path(view->mlx, path);
	if (!image)
		return (0);
	size = view_iterator(view);
	mlx_resize_image(image, view->tile_size.x, view->tile_size.y);
	instance_array = create_inst_matrix(view->mlx, image,
			size);
	if (instance_array == 0)
		return (free_inst_matrix(instance_array, size),
			mlx_delete_image(view->mlx, image), (void *)0);
	view->fg_matrix = instance_array;
	move_matrix(view, image, instance_array, 1);
	view->fg_img = image;
	view->fg_path = path;
	return (image);
}

t_viewprt	*init_viewport(mlx_t *mlx, t_map *map, char *textures[2])
{
	t_viewprt *view;

	view = zeroit(malloc(sizeof(t_viewprt)), sizeof(t_viewprt));
	if (!view)
		return (0);
	view->mlx = mlx;
	view->map = map;
	view->size = (t_position){VIEWPORT_HEIGHT, VIEWPORT_WIDTH};
	view->tile_size = (t_position){mlx->height / VIEWPORT_HEIGHT,
		mlx->width / VIEWPORT_WIDTH};
	view->map_smaller = (t_position){VIEWPORT_HEIGHT > map->height, VIEWPORT_WIDTH > map->width};
	view->map_offset = (t_position){
		(((VIEWPORT_HEIGHT - map->height) / 2) * view->tile_size.y)
			* view->map_smaller.y,
		(((VIEWPORT_WIDTH - map->width) / 2) * view->tile_size.y)
			* view->map_smaller.x};
	if (textures && textures[0] && !init_background(view, textures[0]))
		return (free(view), (void *)0);
	if (textures && textures[0] && !init_foreground(view, textures[1]))
		return (mlx_delete_image(mlx, view->bg_img),
			free(view), (void *)0);
	return (view);
}

void destroy_viewport(t_viewprt *view)
{
	t_list *obj;
	t_view_obj *instance;

	obj = view->objects;
	while (obj)
	{
		instance = (t_view_obj *)obj->content;
		if (instance && instance->destroy)
			instance->destroy(instance, view);
		obj->content = 0;
		obj = obj->next;
	}
	ft_lstclear(&view->objects, free);
	mlx_delete_image(view->mlx, view->bg_img);
	mlx_delete_image(view->mlx, view->fg_img);
	free_inst_matrix(view->fg_matrix, view_iterator(view));
	free(view);
}

void	draw_viewport_hook(void *param)
{
	t_viewprt *view = (t_viewprt *)param;
	draw_viewport(view);
}
