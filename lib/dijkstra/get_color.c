/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 11:00:07 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 11:00:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DIJKSTRA_COLOURS

#include "dijkstra.h"

int	get_colour(void *map, t_dj_position pos)
{
	t_dj_map	*dj_map;

	dj_map = (t_dj_map *)map;
	if (!dj_map->is_valid(dj_map, pos))
		return (3);
	if (dj_map->cost_map[pos.y][pos.x].cost == -1)
		return (2);
	if (pos.x == dj_map->start.x && pos.y == dj_map->start.y)
		return (4);
	return (1);
}
