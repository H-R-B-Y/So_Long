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

int map_all_same_size(t_map_proto map_proto, size_t size[2])
{
	int i;
	size_t width;

	i = 1;
	width = ft_strlen(map_proto[0]);
	width += 1 * (map_proto[0][width] == '\n');
	while (map_proto[i])
	{
		if (ft_strlen(map_proto[i]) != width)
			return (1);
		i++;
	}
	size[0] = width;
	size[1] = i;
	return (0);
}

int	map_has_required(t_map_proto map_proto, int *flags, size_t size[2])
{
	char	*p;
	int 	i;

	i = 0;
	while (map_proto[i])
	{
		p = map_proto[i];
		while (*p)
		{
			if (!ft_strchr(MAP_CHARSET, *p))
				return (1);
			if (*p == MAP_PLAYER && (*flags & 1) != 1)
				*flags |= 1;
			else if (*p == MAP_PLAYER && (*flags & 1) == 1)
				return (1);
			if (*p == MAP_EXIT && (*flags & 2) != 2)
				*flags |= 2;
			else if (*p == MAP_EXIT && (*flags & 2) != 2)
				return (1);
			*flags |= 4 * (*p == MAP_COLLECTIBLE);
			*flags |= 8 * (*p == MAP_EXIT);
		}
	}
	return (0);
}

int		map_surrounded(t_map_proto map_proto, size_t size[2])
{
	size_t	size; // size of the list
	size_t	len; // len of the lines
	char	*temp;

	size = 0;
	len = ft_strlen(map_proto[0]) - (1 * (map_proto[0][len] == '\n'));
	while (map_proto[size])
	{
		if (map_proto[size][0] != MAP_WALL)
			return (1);
		if (map_proto[size][0] != map_proto[size][len])
			return (1);
		size++;
	}
	if (ft_strncmp(map_proto[0], map_proto[size - 1], len))
		return (1);
	temp = malloc(len + 1);
	if (!temp)
		return (1);
	ft_memset(temp, MAP_WALL, len);
	temp[len] = 0;
	if (ft_strncmp(map_proto[0], temp, len))
		return (free(temp), 1);
	return (free(temp), 0);
}
