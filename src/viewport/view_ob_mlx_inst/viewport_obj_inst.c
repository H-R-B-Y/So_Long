/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_obj_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 16:14:44 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 16:14:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
These are example functions that wrap the MLX42 instance to be used as a viewport object.

Note: Because the view object destory function
	is set to free, we need to keep track of the
	img pointer and delete it before killing mlx42
*/

#include "viewport_obj_inst.h"

t_obj_mlx_inst	*create_obj_instance(mlx_t *mlx,
	mlx_image_t *img)
{
	t_obj_mlx_inst	*obj;

	obj = malloc(sizeof(t_obj_mlx_inst));
	if (!obj)
		return (0);
	obj->image = img;
	obj->instance = mlx_image_to_window(mlx, img, 0, 0);
	if (obj->instance < 0)
		return (free(obj), 0);
	obj->image->instances[obj->instance].enabled = 0;
	return (obj);
}

int	enable_instance(t_view_obj *obj, t_viewport *view)
{
	t_obj_mlx_inst	*data;

	if (!obj || !view)
		return (0);
	data = (t_obj_mlx_inst *)obj->data;
	if (!data || !data->image || data->instance < 0)
		return (0);
	data->image[data->instance].enabled = 1;
	return (1);
}

int	disable_instance(t_view_obj *obj, t_viewport *view)
{
	t_obj_mlx_inst	*data;

	if (!obj || !view)
		return (0);
	data = (t_obj_mlx_inst *)obj->data;
	if (!data || !data->image || data->instance < 0)
		return (0);
	data->image[data->instance].enabled = 0;
	return (1);
}
