/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endscreen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-23 16:57:55 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-23 16:57:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*center_txt(char *str, t_game *g, t_position pos)
{
	mlx_image_t	*img;

	img = mlx_put_string(g->mlx, str, 0, 0);
	img->instances[0].x = pos.x - (img->width / 2);
	img->instances[0].y = pos.y - (img->height / 2);
	if (!img)
		return (0);
	return (img);
}

static void game_end(void *g)
{
	t_game	*game;

	game = (t_game *)g;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	return ;
}

int init_end_screen(t_game *g)
{
	mlx_image_t	*img;
	char		*str;

	g->state = GM_WON;
	str = fancy_str_join("You won in ", ft_itoa(g->steps), 2);
	str = fancy_str_join(str, " steps!", 1);
	img = center_txt(
				str, g, (t_position){
					g->mlx->height / 2, g->mlx->width / 2});
	free(str);
	ft_lstadd_back(&g->cleanup, ft_lstnew(img));
	img = center_txt(
				"Press 'ESC' to exit", g, (t_position){
					g->mlx->height / 2
					+ (img->height * 1.8) , g->mlx->width / 2});
	ft_lstadd_back(&g->cleanup, ft_lstnew(img));
	mlx_loop_hook(g->mlx, game_end, g);
	return (1);
}
