/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-25 14:51:28 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-25 14:51:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*create_step_counter(t_game *g)
{
	mlx_image_t	*img;
	char		*str;

	str = fancy_str_join("Steps: ", ft_itoa(g->steps), 2);
	img = mlx_put_string(g->mlx, str, 0, 0);
	img->instances[0].x = 0;
	img->instances[0].y = 0;
	free(str);
	return (img);
}

static mlx_image_t *create_count_counter(t_game *g)
{
	mlx_image_t	*img;
	char		*str;

	str = fancy_str_join(ft_itoa(g->c_count), " / ", 1);
	str = fancy_str_join(str, ft_itoa(g->map->coin_count), 3);
	img = mlx_put_string(g->mlx, str, 0, 0);
	img->instances[0].x = 0;
	img->instances[0].y = (img->height) * 1.8;
	free(str);
	return (img);
}


void	update_step_counter(t_game *g)
{
	if (g->step_img)
		mlx_delete_image(g->mlx, g->step_img);
	g->step_img = create_step_counter(g);
	if (g->coinint_img)
		mlx_delete_image(g->mlx, g->coinint_img);
	g->coinint_img = create_count_counter(g);
}
