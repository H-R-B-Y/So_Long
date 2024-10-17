/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 20:29:12 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 20:29:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim_engine.h"

void	*frame_from_image(void *content)
{
	t_frame		*frame;
	mlx_image_t	*image;

	image = (mlx_image_t *)content;
	frame = zeroit(malloc(sizeof(t_frame)), sizeof(t_frame));
	if (!frame)
		return (0);
	frame->image = image;
	return (frame);
}

t_frame_list	create_frame_list(t_list *image_list, mlx_t *mlx)
{
	t_frame_list	list;
	t_frame_list	this_frame;
	t_frame			*frame;

	list = ft_lstmap(image_list, frame_from_image, free);
	if (!list)
		return (0);
	this_frame = list;
	while (this_frame)
	{
		frame = (t_frame *)this_frame->content;
		frame->instance = mlx_image_to_window(mlx, frame->image, -0, -0);
		frame->image->instances[frame->instance].enabled = 0;
		this_frame = this_frame->next;
	}
	return (list);
}

void	destroy_frame_list(t_frame_list list)
{
	t_frame_list	this_frame;
	t_frame			*frame;

	this_frame = list;
	while (this_frame)
	{
		frame = (t_frame *)this_frame->content;
		frame->image->instances[frame->instance].enabled = 0;
		this_frame = this_frame->next;
	}
	ft_lstclear(&list, free);
}
