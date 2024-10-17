/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:43:46 by hbreeze           #+#    #+#             */
/*   Updated: 2024/10/10 14:54:36 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

// private functions:

/**
 * @brief Check if the map has a path from player to exit
 * @param map map to check
 * @return 1 if map has path, 0 if not
 */
int	_validate_map(t_map *map);

t_map_proto	map_proto_read(int fd)
{
	t_map_proto	map_proto;
	char		*line;
	int			i;
	t_list		*lines;
	t_list		*tmp;

	lines = 0;
	i = 0;
	line = get_next_line(fd);
	while (line > (char *)0 && ++i)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	map_proto = malloc((i + 1) * sizeof(char *));
	if (!map_proto)
		return (ft_lstclear(&lines, &free), (char **)0);
	map_proto[i] = 0;
	tmp = lines;
	while (--i >= 0)
	{
		map_proto[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (ft_lstclear(&lines, &free), map_proto);
}

void	map_proto_free(t_map_proto map_proto)
{
	int	i;

	i = 0;
	while (map_proto[i])
		free(map_proto[i++]);
	free(map_proto);
}

void	free_map(t_map *map)
{
	map_proto_free(map->map);
	if (map->coins)
		ft_lstclear(&map->coins, &free);
	free(map);
}

t_map	*create_map(t_map_proto map_proto)
{
	t_map	*map;

	if (!map_proto)
		return ((t_map *)0);
	map = zeroit(malloc(sizeof(t_map)), sizeof(t_map));
	if (!map)
		return (0);
	map->map = map_proto;
	map->width = ft_strlen(map_proto[0])
		- (map_proto[0][ft_strlen(map_proto[0]) - 1] == '\n');
	while (map_proto[map->height])
		map->height++;
	map->coins = 0;
	map->coin_count = 0;
	if (!_validate_map(map))
		return (free_map(map), (t_map *)0);
	map->size = (t_position){map->height, map->width};
	return (map);
}
