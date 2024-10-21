/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_internal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:15:10 by hbreeze           #+#    #+#             */
/*   Updated: 2024/10/10 14:53:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

// private functions:
int	_map_all_same_size(t_map *map);
int	_map_has_required(t_map *map);
int	_map_surrounded(t_map *map);
int	_map_has_path(t_map *map);

/**
 * @brief Check if the map has a path from player to exit
 * @param map map to check
 * @return 1 if map has path, 0 if not
 */
int	_map_all_same_size(t_map *map)
{
	size_t	i;
	size_t	width;

	i = 1;
	while (map->map[i])
	{
		width = ft_strlen(map->map[i]);
		width -= 1 * (map->map[i][width - 1] == '\n');
		if (width != map->width)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Check if the map has walls
 * @param map map to check
 * @return 1 if map has walls, 0 if not
 */
int	_map_has_walls(t_map *map)
{
	size_t	i;
	char	*p;

	i = 0;
	while (map->map[i])
	{
		if (map->map[i][0] != MAP_WALL
				|| map->map[i][map->width - 1] != MAP_WALL)
			return (0);
		i++;
	}
	if (ft_strncmp(map->map[0], map->map[map->height - 1], map->width))
		return (0);
	p = malloc(map->width + 1);
	if (!p)
		return (0);
	ft_memset(p, MAP_WALL, map->width);
	p[map->width] = 0;
	if (ft_strncmp(map->map[0], p, map->width))
		return (free(p), 0);
	return (free(p), 1);
}

/**
 * @brief Create a position struct
 * @param y y coordinate
 * @param x x coordinate
 * @return t_position* pointer to the created position
 */
t_position	*create_pos(size_t y, size_t x)
{
	t_position	*pos;

	pos = malloc(sizeof(t_position));
	if (!pos)
		return (0);
	pos->y = y;
	pos->x = x;
	return (pos);
}

/**
 * @brief Check if the map has the required elements
 * @param map map to check
 * @return 1 if map has required elements, 0 if not
 */
int	_map_has_requred(t_map *map)
{
	int			flg;
	t_position	i;

	flg = 0;
	i = (t_position){0, 0};
	while (map->map[i.y] && i.y < map->height)
	{
		i.x = 0;
		while (map->map[i.y][i.x] && i.x < map->width - 1)
		{
			if ((map->map[i.y][i.x] == MAP_PLAY && (flg & 1))
				|| (map->map[i.y][i.x] == MAP_EXIT && (flg & 2)))
				return (0);
			if (map->map[i.y][i.x] == MAP_PLAY && ((!(flg & 1) && flg++) || 1))
				map->player = (t_position){i.y, i.x};
			flg = flg | (2 * (map->map[i.y][i.x] == MAP_EXIT));
			if (map->map[i.y][i.x] == MAP_EXIT)
				map->exit = (t_position){i.y, i.x};
			if (map->map[i.y][i.x] == MAP_COIN && ++map->coin_count)
				ft_lstadd_back(&map->coins, ft_lstnew(create_pos(i.y, i.x)));
			i.x++;
		}
		i.y++;
	}
	return ((flg | (4 * !!map->coin_count)) == 7);
}

/**
 * @brief Check if the map has a path from player to exit
 * @param map map to check
 * @return 1 if map has path, 0 if not
 */
int	_validate_map(t_map *map)
{
	if (!_map_all_same_size(map))
		return (0);
	if (!_map_has_walls(map))
		return (0);
	if (!_map_has_requred(map))
		return (map->coin_count = 0, 0);
	if (!_map_has_path(map))
		return (0);
	return (1);
}
