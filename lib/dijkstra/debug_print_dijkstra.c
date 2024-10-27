/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_dijkstra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 10:28:17 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 10:28:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dijkstra.h"
#include "dijkstra_debug.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

static void	print_cost_char(t_dj_map *map, size_t i, size_t j)
{
	if (!map->is_valid(map, (t_dj_position){i, j}))
		ft_putchar_fd('#', 1);
	else if (map->cost_map[i][j].cost == -1)
		ft_putchar_fd(' ', 1);
	else
		ft_putchar_fd((char)map->get_type(map, (t_dj_position){i, j}), 1);
	ft_putchar_fd(' ', 1);
}

static void	print_colour_string(t_dj_map *map,
	t_dj_position pos,
	t_dj_position highlight,
	int (*colour)(void *, t_dj_position)
)
{
	if (pos.y == highlight.y && pos.x == highlight.x)
		ft_putstr_fd(RED, 1);
	else
		ft_putstr_fd(
			((char *[]){WHITE,
				GREEN,
				YELLOW,
				BLUE,
				MAGENTA,
				CYAN,
				RED}
				)[colour(map, (t_dj_position){pos.y, pos.x})],
			1
			);
}

void	debug_print_dijkstra(
	t_dj_map *map,
	t_dj_position highlight,
	int (*colour)(void *, t_dj_position)
)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			print_colour_string(map, (t_dj_position){i, j},
				highlight, colour);
			print_cost_char(map, i, j);
			ft_putstr_fd(RESET, 1);
			j++;
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
