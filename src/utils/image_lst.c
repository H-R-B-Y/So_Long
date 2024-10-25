/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-22 09:38:41 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-22 09:38:41 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	backwards_delete(t_game *g,
			t_list *ls, size_t i)
{
	while (i)
	{
		mlx_delete_image(g->mlx,
			((mlx_image_t *)ft_lstget(ls, i)
				->content));
		free(ft_lstget(ls, i));
		i--;
	}
}

t_list	*init_img_lst(
		t_game *g, char **paths,
		t_position size)
{
	t_list *ls;
	mlx_image_t *img;
	size_t i;

	ls = 0;
	i = 0;
	if (!g || !paths)
		return (0);
	while (paths[i])
	{
		img = image_from_path(g->mlx, paths[i]);
		if (img && ++i)
			ft_lstadd_back(&ls, ft_lstnew(img));
		else
			return (backwards_delete(g, ls, i), (void *)0);
		mlx_resize_image(img, size.x, size.y);
	}
	return (ls);
}
