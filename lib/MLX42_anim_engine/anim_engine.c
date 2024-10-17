/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 19:29:25 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 19:29:25 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim_engine.h"

t_anim_engine	*anim_engine_init(mlx_t *mlx)
{
	t_anim_engine	*engine;

	engine = (t_anim_engine *)malloc(sizeof(t_anim_engine));
	if (!engine)
		return (0);
	engine->sprite_list = 0;
	engine->mlx = mlx;
	return (engine);
}

static void	destory_anim_sprite_wrapper(void *content)
{
	anim_destroy_sprite((t_anim_sprite *)content);
}

void	anim_engine_cleanup(t_anim_engine *engine)
{
	t_list	*sprite_list;

	sprite_list = engine->sprite_list;
	ft_lstclear(&sprite_list, destory_anim_sprite_wrapper);
	free(engine);
}
