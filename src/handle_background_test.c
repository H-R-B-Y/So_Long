/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_background_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 12:25:45 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 12:25:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <math.h>

# include "../include/MLX42.h"
# include "../include/libft.h"
# include "../include/anim_engine.h"
# include "./so_long.h"

# define BG_PNG "../assets/bg.png"
# define FG_PNG "../assets/fg.png"

typedef struct viewport_s
{
	mlx_t		*mlx;
	size_t		width;
	size_t		height;
	size_t		map_offset[2];
	mlx_image_t	*background;
	mlx_image_t	*foreground;
	int			**fore_instances;
	int			**map;
	double			re_draw_delta;
}	t_viewport;

int _draw_fore_back(t_viewport *viewport, size_t scale_y, size_t scale_x)
{
	size_t x;
	size_t y;

	if (!mlx_resize_image(viewport->foreground, scale_x, scale_y) 
		|| !mlx_resize_image(viewport->background, scale_x, scale_y))
		return (0);
	viewport->fore_instances = malloc(sizeof(int *) * viewport->height);
	y = 0;
	while (y < viewport->height)
	{
		viewport->fore_instances[y] = malloc(sizeof(int) * viewport->width);
		x = 0;
		while (x < viewport->width)
		{
			mlx_image_to_window(viewport->mlx, viewport->background, x * scale_x, y * scale_y);
			viewport->fore_instances[y][x] =
				mlx_image_to_window(viewport->mlx, viewport->foreground, x * scale_x, y * scale_y);
			viewport->foreground->instances[viewport->fore_instances[y][x]].enabled = 0;
			x++;
		}
		y++;
	}
	return (1);
}

t_viewport *init_viewport(mlx_t *mlx, char *foreground_path, char *background_path)
{
	t_viewport *viewport;
	mlx_texture_t *foreground;
	mlx_texture_t *background;

	if (!mlx || !foreground_path || !background_path)
		return (0);
	viewport = zeroit(malloc(sizeof(t_viewport)), sizeof(t_viewport));
	if (!viewport)
		return (0);
	viewport->mlx = mlx;
	viewport->width = mlx->width;
	viewport->height = mlx->height;
	background = mlx_load_png(background_path);
	foreground = mlx_load_png(foreground_path);
	if (!background || !foreground)
	{
		free(viewport);
		return (0);
	}
	viewport->background = mlx_texture_to_image(mlx, background);
	viewport->foreground = mlx_texture_to_image(mlx, foreground);
	mlx_delete_texture(background);
	mlx_delete_texture(foreground);
	viewport->fore_instances = malloc(sizeof(int *) * viewport->height);
	if (!viewport->background || !viewport->foreground)
	{
		free(viewport);
		return (0);
	}
	_draw_fore_back(viewport, viewport->height / VIEWPORT_HEIGHT, viewport->width / VIEWPORT_WIDTH);
	viewport->re_draw_delta = 0;
	return (viewport);
}

// ASSUMES the map is drawable
// Need to write a function that can convert a dijkstra map to a viewport map;
void draw_viewport(t_viewport *viewport, int **map)
{
	size_t x;
	size_t y;

	if (!viewport || !map)
		return ;
	y = 0;
	while (y < VIEWPORT_HEIGHT)
	{
		x = 0;
		while (x < VIEWPORT_WIDTH)
		{
			if (map[y][x])
				viewport->foreground->instances[viewport->fore_instances[y][x]].enabled = 1;
			else
				viewport->foreground->instances[viewport->fore_instances[y][x]].enabled = 0;
			x++;
		}
		y++;
	}
}

void destroy_viewport(t_viewport *viewport)
{
	size_t y;

	if (!viewport)
		return ;
	y = 0;
	while (y < VIEWPORT_HEIGHT)
	{
		free(viewport->fore_instances[y]);
		y++;
	}
	free(viewport->fore_instances);
	mlx_delete_image(viewport->mlx, viewport->foreground);
	mlx_delete_image(viewport->mlx, viewport->background);
	free(viewport);
}

void re_draw(int **map, t_viewport *viewport)
{
	size_t y = 0;
	size_t x;
	while (y < VIEWPORT_HEIGHT)
	{
		x = 0;
		while (x < VIEWPORT_WIDTH)
		{
			map[y][x] = rand() % 2;
			x++;
		}
		y++;
	}
	draw_viewport(viewport, map);
}

void loop_hook (void *param)
{
	t_viewport *viewport = (t_viewport *)param;
	
	viewport->re_draw_delta += viewport->mlx->delta_time;
	if (viewport->re_draw_delta > 0.5)
	{
		re_draw(viewport->map, viewport);
		viewport->re_draw_delta = 0;
	}
}


int main ()
{
	mlx_t *mlx = mlx_init(1600, 900, "Anim engine test", false);

	t_viewport *viewport = init_viewport(mlx, FG_PNG, BG_PNG);
	int **map = malloc(sizeof(int *) * 9);
	size_t y = 0;
	size_t x;
	while (y < VIEWPORT_HEIGHT)
	{
		map[y] = malloc(sizeof(int) * 16);
		x = 0;
		while (x < VIEWPORT_WIDTH)
		{
			map[y][x] = rand() % 2;
			x++;
		}
		y++;
	}
	draw_viewport(viewport, map);
	viewport->map = map;
	mlx_loop_hook(mlx, loop_hook, viewport);
	mlx_loop(mlx);
	destroy_viewport(viewport);
	y = 0;
	while (y < VIEWPORT_HEIGHT)
	{
		free(map[y]);
		y++;
	}
	free(map);
	mlx_terminate(mlx);
	return (0);
}