/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_instance_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 15:06:48 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 15:06:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_intance_pos(mlx_instance_t *instance, t_position pos, int depth)
{
	instance->y = (int) clamp(pos.y, 0, __INT_MAX__);
	instance->x = (int) clamp(pos.x, 0, __INT_MAX__);
	mlx_set_instance_depth(instance, depth);
}
