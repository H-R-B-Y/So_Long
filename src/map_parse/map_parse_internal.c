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

/*
Reads the map proto from a file descriptor.
@fd: file descriptor to read from
@returns: map proto (2D char array), NULL if malloc fails or read fails.
*/
t_map_proto		_map_proto_read(int fd)
{
	t_map_proto	map_proto;
	char		*line;
	int			i;
	t_list		*lines;
	t_list		*tmp;

	lines = 0;
	i = 0;
	while ((line = get_next_line(fd)) > 0 && ++i) // Note: line is malloc'd here
		ft_lstadd_back(&lines, ft_lstnew(line)); // Note: list is malloc'd here
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
	ft_lstclear(&lines, free);
	return (map_proto);
}

/*
Frees the map proto.
@map_proto: map proto to free
*/
void			_map_proto_free(t_map_proto map_proto)
{
	int	i;

	i = 0;
	while (map_proto[i])
		free(map_proto[i++]);
	free(map_proto);
}

/*
Validates the map proto.
@map_proto: map proto to validate
@returns: 1 if valid, 0 if invalid.
*/
int				_map_proto_validate(t_map_proto map_proto, size_t size[2])
{
	int flags;

	flags = 0;
	if (map_all_same_size(map_proto, size))
		return (0);
	if (map_has_required(map_proto, &flags))
		return (0);
	if (flags != 15)
		return (0);
	if (map_surrounded(map_proto))
		return (0);
	return (1);
}

/*
Parses the map proto into a map struct.
Note: The map struct should contain a copy of the map proto.
Note: The map proto will not be freed on error.
@map_proto: map proto to parse
@returns: map struct, NULL if error.
*/
t_map			*_map_parse_proto(t_map_proto map_proto)
{
	t_map	*map;

	map = zeroit(malloc(sizeof(t_map)), sizeof(t_map));
	if (!map)
		return (0);
	*map = (t_map){
		.width = ft_strlen(map_proto[0]) - (1 * map_proto[0][ft_strlen(map_proto[0]) - 1] == '\n'),
		.height = 0,
		.map = map_proto
	};
	while (map_proto[map->height])
		map->height++;
	return (map);
}
