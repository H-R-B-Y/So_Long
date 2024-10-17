/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_from_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 15:05:37 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 15:05:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

mlx_image_t	*image_from_path(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (0);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (0);
	return (image);
}
