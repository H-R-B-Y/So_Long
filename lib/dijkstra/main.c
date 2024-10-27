/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 16:56:54 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 16:56:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dijkstra.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int	is_valid(void *map, t_dj_position pos)
{
	t_dj_map	*dj_map;
	t_list		*line;

	dj_map = (t_dj_map *)map;
	line = dj_map->map;
	while (pos.y && pos.y-- && line)
		line = line->next;
	if (!line || pos.y)
		return (0);
	return (((char *)line->content)[pos.x] != '#');
}

int	get_type(void *map, t_dj_position pos)
{
	t_dj_map	*dj_map;
	t_list		*line;

	dj_map = (t_dj_map *)map;
	line = dj_map->map;
	while (pos.y && pos.y-- && line)
		line = line->next;
	if (!line || pos.y)
		return (0);
	return (((char *)line->content)[pos.x]);
}

int	setup_map(char *path,
	t_dj_map *map,
	t_list *my_map
)
{
	int		fd;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (2);
	my_map->content = get_next_line(fd);
	tmp = get_next_line(fd);
	while (tmp && *tmp != '\n')
	{
		ft_lstadd_back(&my_map, ft_lstnew(tmp));
		if (ft_strchr(tmp, 'P'))
			map->start = (t_dj_position){ft_lstsize(my_map) - 1,
				ft_strchr(tmp, 'P') - tmp};
		tmp = get_next_line(fd);
	}
	if (tmp && *tmp == '\n')
		free(tmp);
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list		*my_map;
	t_dj_map	map;

	if (argc != 2)
		return (1);
	my_map = malloc(sizeof(t_list));
	zeroit(&map, sizeof(t_dj_map));
	if (!my_map)
		return (3);
	my_map->content = 0;
	my_map->next = 0;
	if (setup_map(argv[1], &map, my_map))
		return (2);
	map.width = ft_strlen(my_map->next->content) - 1;
	map.height = ft_lstsize(my_map);
	map.map = my_map;
	map.is_valid = is_valid;
	map.get_type = get_type;
	perform_dijkstra(&map);
	dijkstra_clean_up(&map);
	ft_lstclear(&my_map, &free);
	return (0);
}
