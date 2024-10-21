/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_obj_anim.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-19 13:24:40 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-19 13:24:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_OBJ_ANIM_H
# define VIEW_OBJ_ANIM_H

# include "../viewport.h"

typedef struct s_view_obj t_view_obj;


/**
 * @brief Create an animation instance
 */
t_view_obj	*create_anim_instance(t_position pos, int depth,
	t_anim_sprite *sprite);

int enable_anim_instance(t_view_obj *obj, t_viewprt *view);


int disable_anim_instance(t_view_obj *obj, t_viewprt *view);

void destroy_anim_instance(void *data, t_viewprt *view);

#endif