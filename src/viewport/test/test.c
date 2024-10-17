/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 17:00:10 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 17:00:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

#define BG_PNG "../../../assets/bg.png"
#define FG_PNG "../../../assets/fg.png"

#include "fcntl.h"

static void ft_hook(void* param)
{
	t_viewport *view = param;
	
}

int main(void)
{
	mlx_t *mlx = mlx_init(1600, 900, "Viewport Test", false);
	int fd = open("../../../lib/map_parse/test/test_maps/valid2", O_RDONLY);
	t_map *my_map = create_map(map_proto_read(fd));
	close(fd);
	t_viewport *viewport = init_viewport(mlx, my_map, (char *[]){BG_PNG, FG_PNG});
	viewport->need_redraw = 1;
	draw_viewport(viewport);

	mlx_loop(mlx);
	destroy_viewport(viewport);
	free_map(my_map);
	mlx_terminate(mlx);
	return (0);
}
