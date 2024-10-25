/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 20:12:49 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 20:12:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_position	min_pos(t_position a, t_position b)
{
	return ((t_position){a.y * (a.y < b.y) + b.y * (a.y >= b.y),
		a.x * (a.x < b.x) + b.x * (a.x >= b.x)});
}

t_position	max_pos(t_position a, t_position b)
{
	return ((t_position){a.y * (a.y >= b.y) + b.y * (a.y < b.y),
		a.x * (a.x >= b.x) + b.x * (a.x > b.x)});
}
