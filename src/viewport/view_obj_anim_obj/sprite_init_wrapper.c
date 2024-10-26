/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init_wrapper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 09:38:56 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-18 09:38:56 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view_obj_anim.h"

static void	__err_img_list(mlx_t *mlx, t_list *lst)
{
	t_list	*index;

	index = lst;
	while (index)
	{
		if (index->content)
			mlx_delete_image(mlx,
				(mlx_image_t *)index->content);
		index = index->next;
	}
	return ;
}

t_anim_sprite	*init_sprite_var(mlx_t *mlx,
	t_position size,
	t_anim_engine *engine,
	char *paths[])
{
	t_anim_sprite	*sprite;
	mlx_image_t		*image;
	t_list			*img_list;

	(void)size;
	img_list = 0;
	while (*paths)
	{
		image = image_from_path(mlx, *paths);
		if (!image)
			return (__err_img_list(mlx, img_list), (void *)0);
		mlx_resize_image(image, size.x, size.y);
		ft_lstadd_back(&img_list, ft_lstnew(image));
		paths++;
	}
	sprite = anim_sprite_create(engine, create_frame_list(img_list, mlx), 1);
	if (!sprite)
		return (__err_img_list(mlx, img_list), (void *)0);
	sprite->context = img_list;
	return (sprite);
}

t_view_obj	*create_anim_instance(t_position pos, int depth,
	t_anim_sprite *sprite)
{
	t_view_obj	*view_obj;

	if (!sprite)
		return (0);
	anim_set_state(sprite, 0);
	view_obj = create_viewport_obj(pos, sprite,
			enable_anim_instance, disable_anim_instance);
	if (!view_obj)
		return (0);
	view_obj->depth = depth;
	view_obj->destroy = destroy_anim_instance;
	return (view_obj);
}
