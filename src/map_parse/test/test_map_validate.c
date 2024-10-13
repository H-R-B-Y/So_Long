/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 07:39:00 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 07:39:00 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../map_parse.h"
#include <fcntl.h>

int main (int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr_fd("Usage: test_map_validate <map_file>\n", 2);
		return (1);
	}

	while (--argc > 0)
	{
		int fd = open(argv[argc], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Failed to open file: ", 2);
			ft_putstr_fd(argv[argc], 2);
			ft_putstr_fd("\n", 2);
			continue;
		}
		t_map *this_map = create_map(map_proto_read(fd));
		close(fd);
		if (!this_map)
		{
			ft_putstr_fd("Failed to create map from file: ", 2);
			ft_putstr_fd(argv[argc], 2);
			ft_putstr_fd("\n", 2);
			close(fd);
			continue;
		}
		free_map(this_map);
		ft_putstr_fd("Map is valid\n", 1);
	}
}