/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 15:03:38 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 15:03:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

t_position min_pos(t_position a, t_position b)
{
	return ((t_position){a.y < b.y ? a.y : b.y,
			a.x < b.x ? a.x : b.x});
}

void	free_instance_matrix(int **instances, t_position size)
{
	t_position	iter;

	iter = (t_position){0, 0};
	while (iter.y < size.y)
		free(instances[iter.y++]);
	free(instances);
}
void	move_matrix(t_viewport *view,
	mlx_image_t *parent,
	int **instance_matrix,
	int depth)
{
	t_position	iter;
	t_position	size;

	size = min_pos(view->viewport_size, view->map->size);
	iter = (t_position){0, 0};
	while (iter.y < size.y)
	{
		iter.x = 0;
		while (iter.x < size.x)
		{
			set_intance_pos(
				&parent->instances[instance_matrix[iter.y][iter.x]],
				(t_position){
					view->map_offset.y
						+ (iter.y * view->tile_size[0]),
					view->map_offset.x
						+ (iter.x * view->tile_size[1])}, depth);
			iter.x++;
		}
		iter.y++;
	}
}

int	**create_instance_matrix(mlx_t *mlx,
	mlx_image_t	*img,
	t_position	size
	)
{
	int			**instances;
	t_position	iter;

	instances = malloc(sizeof(int *) * size.y);
	if (!instances)
		return (0);
	iter = (t_position){0, 0};
	while (iter.y < size.y)
	{
		instances[iter.y] = malloc(sizeof(int) * size.x);
		if (!instances[iter.y])
			return (free_instance_matrix(instances,
					(t_position){iter.y, size.x}), (void *)0);
		iter.x = 0;
		while (iter.x < size.x)
		{
			instances[iter.y][iter.x]
				= mlx_image_to_window(mlx, img, 0, 0);
			if (instances[iter.y][iter.x++] < 0)
				return (free_instance_matrix(instances,
						(t_position){iter.y, size.x}), (void *)0);
		}
		iter.y++;
	}
	return (instances);
}