/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-12 19:07:24 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-12 19:07:24 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"
#include "include/dijkstra.h"

/**
 * @brief Check if all coins and exit have a path to player
 * @param cost_map cost map to check
 * @param map map to check
 * @return 1 if all coins and exit have a path, 0 if not
 */
int	_paths_to_rome(t_cost_map cost_map, t_map *map)
{
	size_t		i;
	t_list		*this_coin;
	t_position	*this_pos;

	i = 0;
	this_coin = map->coins;
	while (i < map->coin_count - 1)
	{
		this_pos = this_coin->content;
		if (cost_map[this_pos->y][this_pos->x].cost == -1)
			return (0);
		this_coin = this_coin->next;
		i++;
	}
	if (cost_map[map->exit.y][map->exit.x].cost == -1)
		return (0);
	return (1);
}

/**
 * @brief Check if a cell is valid
 * @param map map to check
 * @param pos position to check
 * @return 1 if cell is valid, 0 if not
 * @note This function is needed for Dijkstra's algorithm
 */
int	is_valid(void *map, t_dj_position pos)
{
	t_dj_map	*dj_map;
	t_map_proto	line;

	if (!map)
		return (0);
	dj_map = (t_dj_map *)map;
	line = dj_map->map;
	if (line[pos.y][pos.x] == MAP_WALL)
		return (0);
	return (1);
}

/**
 * @brief Get the type of a cell
 * @param map map to get type from
 * @param pos position to get type of
 * @return type of cell
 * @note This function is needed for Dijkstra's algorithm
 */
int	get_type(void *map, t_dj_position pos)
{
	t_dj_map	*dj_map;
	t_map_proto	line;

	if (!map)
		return (0);
	dj_map = (t_dj_map *)map;
	line = dj_map->map;
	return (line[pos.y][pos.x]);
}

/**
 * @brief Check if the map has a path from player to exit
 * @param map map to check
 * @return 1 if map has path, 0 if not
 */
int	_map_has_path(t_map *map)
{
	t_dj_map	dj_map;

	dj_map.width = map->width;
	dj_map.height = map->height;
	dj_map.map = map->map;
	dj_map.start = (t_dj_position){map->player.y, map->player.x};
	dj_map.is_valid = is_valid;
	dj_map.get_type = get_type;
	perform_dijkstra(&dj_map);
	if (!_paths_to_rome(dj_map.cost_map, map))
	{
		dijkstra_clean_up(&dj_map);
		return (0);
	}
	dijkstra_clean_up(&dj_map);
	return (1);
}
