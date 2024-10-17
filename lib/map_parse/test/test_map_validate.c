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

void	read_file(char *filename)
{
	int		fd;
	t_map	*this_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Failed to open file: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	this_map = create_map(map_proto_read(fd));
	close(fd);
	if (!this_map)
	{
		ft_putstr_fd("Failed to create map from file: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		close(fd);
		return ;
	}
	free_map(this_map);
	ft_putstr_fd("Map is valid\n", 1);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr_fd("Usage: test_map_validate <map_file>\n", 2);
		return (1);
	}
	while (*++argv)
		read_file(*argv);
	return (0);
}
