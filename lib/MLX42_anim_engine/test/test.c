/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 21:18:27 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 21:18:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/MLX42.h"
#include "../include/libft.h"
#include "../anim_engine.h"

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.


t_list *create_image_list(mlx_t *mlx)
{
	t_list *list;
	mlx_texture_t *texture;
	mlx_image_t *image;

	texture = mlx_load_png("./anim/frame1.png");
	if (!texture)
		ft_error();
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
		ft_error();
	list = ft_lstnew(image);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./anim/frame2.png");
	if (!texture)
		ft_error();
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
		ft_error();
	ft_lstadd_back(&list, ft_lstnew(image));
	mlx_delete_texture(texture);
	texture = mlx_load_png("./anim/frame3.png");
	if (!texture)
		ft_error();
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
		ft_error();
	ft_lstadd_back(&list, ft_lstnew(image));
	mlx_delete_texture(texture);
	return (list);
}

int main(void)
{
	t_anim_engine *engine;
	t_anim_sprite *sprite;
	t_list *image_list;
	t_list *index;

	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Anim engine test", false);

	engine = zeroit(malloc(sizeof(t_anim_engine)), sizeof(t_anim_engine));
	engine->mlx = mlx;
	// create a list of images
	image_list = create_image_list(mlx);
	// call to create frame list
	t_frame_list frame_list = create_frame_list(image_list, mlx);
	// create a sprite
	sprite = anim_sprite_create(engine, frame_list, 0.1);
	anim_set_loop(sprite, anim_loop_backward, 1);
	anim_set_pos(sprite, 0, 0, 0);
	anim_set_state(sprite, 1);

	frame_list = create_frame_list(image_list, mlx);
	sprite = anim_sprite_create(engine, frame_list, 0.2);
	anim_set_loop(sprite, anim_loop_forward, 1);
	anim_set_pos(sprite, 40, 40, 0);
	anim_set_state(sprite, 1);

	frame_list = create_frame_list(image_list, mlx);
	sprite = anim_sprite_create(engine, frame_list, 0.4);
	anim_set_loop(sprite, anim_loop_pingpong, 1);
	anim_set_pos(sprite, 80, 80, 0);
	anim_set_state(sprite, 1);

	frame_list = create_frame_list(image_list, mlx);
	sprite = anim_sprite_create(engine, frame_list, 0.8);
	anim_set_loop(sprite, anim_loop_backward, 1);
	anim_set_pos(sprite, 120, 120, 0);
	anim_set_state(sprite, 1);

	// create the loop callback
	mlx_loop_hook(mlx, anim_update_hook, engine);
	mlx_loop(mlx);
	anim_engine_cleanup(engine);
	index = image_list;
	while (index)
	{
		mlx_delete_image(mlx, (mlx_image_t *)index->content);
		index->content = 0;
		index = index->next;
	}
	ft_lstclear(&image_list, free);
	mlx_terminate(mlx);
	return (0);
}

