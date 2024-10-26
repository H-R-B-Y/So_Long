/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_obj_inst.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 16:33:45 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 16:33:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_OBJ_INST_H
# define VIEWPORT_OBJ_INST_H

# include "../viewport.h"

/*
These are examples of how to utilize the viewport objects,
using MLX42 images as an example.
*/

/**
 * @brief Structure to hold the MLX42 instance
 * @param image Pointer to the image
 * @param instance Instance of the image
 */
typedef struct s_frame	t_obj_mlx_inst;

/**
 * @brief Create a new MLX42 instance
 * @param mlx Pointer to the MLX42 instance
 * @param img Pointer to the image
 * @return Pointer to the new instance if successful, 0 if not
 */

t_obj_mlx_inst	*create_obj_instance(mlx_t *mlx,
					mlx_image_t *img);

/**
 * @brief Enable the instance
 * @param obj Pointer to the object
 * @param view Pointer to the viewport
 */
int				enable_instance(t_view_obj *obj,
					t_viewprt *view);

/**
 * @brief Disable the instance
 * @param obj Pointer to the object
 * @param view Pointer to the viewport
 */
int				disable_instance(t_view_obj *obj,
					t_viewprt *view);

#endif