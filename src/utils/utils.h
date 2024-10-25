/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 15:04:47 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 15:04:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../include/MLX42.h"
# include "../../include/map_parse.h"
# include "../../include/anim_engine.h"

/*
Just some utility functions that don't really fit anywhere else
*/

t_position	min_pos(t_position a, t_position b);

t_position	max_pos(t_position a, t_position b);

mlx_image_t	*image_from_path(mlx_t *mlx, char *path);

void		set_intance_pos(mlx_instance_t *instance,
				t_position pos, int depth);

int			clamp(int value, int min, int max);

void		destroy_image_lst(mlx_t *mlx, t_list *lst);

#endif