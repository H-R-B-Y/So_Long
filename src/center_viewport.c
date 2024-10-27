/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 17:55:47 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-26 17:55:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void center_viewport(t_viewprt *v, t_position p)
{
	t_position	off;

	off = (t_position){
		(p.y - (v->size.y / 2)) * (!v->map_smaller.y),
		(p.x - (v->size.x / 2)) * (!v->map_smaller.x)
		};
	v->offset = off;
	v->need_redraw = 1;
}