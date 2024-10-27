/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_queue_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 16:35:19 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 16:35:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dijkstra.h"

int	init_cost_map(t_dj_map *map)
{
	t_dj_position	iter;
	t_cost_map		cost_map;

	cost_map = malloc(map->height * sizeof(t_cell *));
	iter = (t_dj_position){0, 0};
	if (!cost_map)
		return (0);
	while (iter.y < map->height)
	{
		cost_map[iter.y] = malloc(map->width * sizeof(t_cell));
		if (!cost_map[iter.y])
			while (iter.y--)
				free(cost_map[iter.y]);
		if (!cost_map[iter.y])
			return (free(cost_map), 0);
		iter.x = 0;
		while (iter.x < map->width)
		{
			cost_map[iter.y][iter.x] = (t_cell){{iter.y, iter.x}, -1, 0};
			iter.x++;
		}
		iter.y++;
	}
	map->cost_map = cost_map;
	return (1);
}

void	dj_enqueue(t_queue **queue, t_cell *cell, int cost)
{
	cell->cost = cost;
	ft_lstadd_back(queue, ft_lstnew(cell));
}

t_cell	*dj_dequeue(t_queue **queue)
{
	t_queue	*node;
	t_cell	*cell;

	node = *queue;
	if (!node)
		return (0);
	*queue = node->next;
	cell = node->content;
	free(node);
	return (cell);
}

void	dijkstra_clean_up(t_dj_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		free(map->cost_map[i]);
		i++;
	}
	free(map->cost_map);
}
