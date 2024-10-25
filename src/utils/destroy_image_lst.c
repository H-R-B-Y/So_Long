/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_image_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-21 17:13:57 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-21 17:13:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	destroy_image_lst(mlx_t *mlx, t_list *images)
{
	t_list	*strt;

	if (!images || !mlx)
		return ;
	strt = images;
	while (images)
	{
		mlx_delete_image(mlx, ((mlx_image_t *)images->content));
		images->content = 0;
		images = images->next;
	}
	ft_lstclear(&strt, free);
}
