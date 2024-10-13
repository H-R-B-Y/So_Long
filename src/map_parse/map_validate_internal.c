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
int				_map_all_same_size(t_map *map);
int				_map_has_required(t_map *map);
int				_map_surrounded(t_map *map);
int				_map_has_path(t_map *map);

int _map_all_same_size(t_map *map)
{
	size_t i;
	size_t width;

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

int _map_has_walls(t_map *map)
{
	size_t i;
	char *p;

	i = 0;
	while (map->map[i])
	{
		if (map->map[i][0] != MAP_WALL || map->map[i][map->width - 1] != MAP_WALL)
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

t_position *create_position(size_t y, size_t x)
{
	t_position *pos;

	pos = malloc(sizeof(t_position));
	if (!pos)
		return (0);
	pos->y = y;
	pos->x = x;
	return (pos);
}

int _map_has_requred(t_map *map)
{
	int flags;
	size_t i;
	size_t j;

	i = 1;
	flags = 0;
	while(map->map[i] && i < map->height)
	{
		j = 1;
		while(map->map[i][j] && j < map->width - 1)
		{
			if ((map->map[i][j] == MAP_PLAY && (flags & 1)) ||
				(map->map[i][j] == MAP_EXIT && (flags & 2)))
					return (0);
			if (map->map[i][j] == MAP_PLAY && (flags |= 1))
				map->player = (t_position){i, j};
			if (map->map[i][j] == MAP_EXIT && (flags |= 2))
				map->exit = (t_position){i, j};
			if (map->map[i][j] == MAP_COIN && map->coin_count++)
				ft_lstadd_back(&map->coins, ft_lstnew(create_position(i, j)));
			j++;
		}
		i++;
	}
	return ((flags | (4 * !!map->coin_count)) == 7);
}

int _validate_map(t_map *map)
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
