/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 19:10:38 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 19:10:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_ENGINE_H
# define ANIM_ENGINE_H

# include "MLX42.h"
# include "libft.h"

# include <stdlib.h>


typedef struct	s_frame t_frame;
typedef struct	s_anim_sprite t_anim_sprite;
typedef size_t	(*t_loop_type)(t_anim_sprite *sprite);
typedef t_list	*t_frame_list;
typedef struct	s_anim_engine t_anim_engine;

/**
 * @brief Structure to hold a frame.
 * @param image MLX image for the frame.
 * @param instance The index in the instance list of this sprite.
 */
struct s_frame
{
	mlx_image_t	*image;
	int			instance;
};

/**
 * @brief Structure to hold an animated sprite.
 * @param frame_list The list of frames to animate.
 * @param frame_count The number of frames in the list.
 * @param current_frame The index of the current frame.
 * @param frame_duration The duration of each frame.
 * @param frame_timer The time since the last frame change.
 * @param x The x position of the sprite.
 * @param y The y position of the sprite.
 * @param z The z position of the sprite or depth.
 * @param enabled Whether the sprite is enabled.
 * @param loop_enabled Whether the loop is enabled.
 * @param finished Whether the animation is finished (only when loop disabled).
 * @param loop The loop function.
 * @param context Additional data, if needed.
 */
struct s_anim_sprite
{
	t_frame_list		frame_list;
	size_t				frame_count;
	size_t				current_frame;
	double				frame_duration;
	double				frame_timer;
	int					x;
	int					y;
	int					z; // not sure how relevant this is
	short				enabled;
	short				loop_enabled;
	short 				finished;
	t_loop_type			loop;
	void				*context;
};

/**
 * @brief Internal function to create a frame from an image.
 * @param sprite_list The list of currently animated sprites.
 * @param mlx The MLX instance handle.
 * @param paused Whether the engine is paused.
 */
struct s_anim_engine
{
	t_list		*sprite_list;
	mlx_t		*mlx;
	int 		paused;
};

/**
 * @brief Internal function to create a frame from an image.
 * @param content The image to create the frame from.
 * @return The created frame or null on failure.
 */
void			*frame_from_image(void *content);

/**
 * @brief Destroys a frame list.
 * @param list The list to destroy.
 * @note This doesn't delete the instances just disables them
 */
void			destroy_frame_list(t_frame_list list);

/**
 * @brief Creates a frame list from an image list.
 * @param image_list The list of images to create the frame list from.
 * @param mlx The MLX instance handle.
 * @return The created frame list or null on failure.
 */
t_frame_list	create_frame_list(t_list *image_list, mlx_t *mlx);

/**
 * @brief Initializes the animation engine.
 * @param mlx The MLX instance handle.
 * @return The animation engine or null on failure.
 */
t_anim_engine	*anim_engine_init(mlx_t *mlx);

/**
 * @brief Cleans up the animation engine.
 * @param engine The engine to clean up.
 * @note This function will also clean up all sprites.
 */
void			anim_engine_cleanup(t_anim_engine *engine);

/**
 * @brief Creates a new animation sprite.
 * @param engine The engine to create the sprite with.
 * @param frame_list The list of frames to animate.
 * @param frame_duration The duration of each frame.
 * @return The created sprite or null on failure.
 */
t_anim_sprite	*anim_sprite_create(t_anim_engine *engine, t_list *frame_list, double frame_duration);

/**
 * @brief Destroys an animation sprite.
 * @param sprite The sprite to destroy.
 * @note This will also delete the frame list.
 */
void			anim_destroy_sprite(t_anim_sprite *sprite);

/**
 * @brief Sets the loop type of the sprite.
 * @param sprite The sprite to set the loop type of.
 * @param loop The loop type.
 * @param loop_enabled Whether the loop is enabled.
 */
void			anim_set_loop(t_anim_sprite *sprite, t_loop_type loop, short loop_enabled);

/**
 * @brief Sets the position of the sprite.
 * @param sprite The sprite to set the position of.
 * @param x The x position.
 * @param y The y position.
 * @param z The z position.
 * @note This function will also set the position of all frames.
 */
void			anim_set_pos(t_anim_sprite *sprite, int32_t x, int32_t y, int32_t z);

/**
 * @brief Sets the enabled state of the sprite.
 * 
 * @note This needs to ensure that the sprite is in a valid state before enabling.
 * 
 * @param sprite The sprite to set the enabled state of.
 * @param enabled The enabled state.
 * @return 1 if the state was set, 0 if not.
 */
int				anim_set_state(t_anim_sprite *sprite, short enabled);

/**
 * @brief Updates the sprite.
 * @param sprite The sprite to update.
 */
void			anim_sprite_update(t_anim_sprite *sprite);

/**
 * @brief Updates all animation objects in the engine.
 * @param engine The engine to update.
 * @note This function will only update sprites that need an update.
 */
void			anim_engine_update(t_anim_engine *engine);

/**
 * @brief The update hook for the animation engine.
 * @param param The engine to update.
 * @note This function is meant to be used as a loop hook.
 */
void			anim_update_hook(void* param);

/**
 * @brief Checks if the sprite needs an update.
 * @param sprite The sprite to check.
 * @param delta_time The time since the last update.
 * @return 1 if the sprite needs an update, 0 if not.
 */
int				anim_needs_update(t_anim_sprite *sprite, double delta_time);

/**
 * @brief Gets a frame from the sprite.
 * @param sprite The sprite to get the frame from.
 * @param index The index of the frame.
 * @return The frame or null on failure.
 */
t_frame			*get_frame(t_anim_sprite *sprite, size_t index);

/**
 * @brief Gets the current frame of the sprite.
 * @param sprite The sprite to get the current frame of.
 * @return The current frame or null on failure.
 */
t_frame			*get_current_frame(t_anim_sprite *sprite);

// Loop types

/**
 * @brief Forward loop type.
 * @param sprite The sprite to loop.
 * @note Will set the sprite to finished if loop is disabled.
 */
size_t			anim_loop_forward(t_anim_sprite *sprite);

/**
 * @brief Backward loop type.
 * @param sprite The sprite to loop.
 * @note Will set the sprite to finished if loop is disabled.
 */
size_t			anim_loop_backward(t_anim_sprite *sprite);

/**
 * @brief Pingpong loop type.
 * @param sprite The sprite to loop.
 * @note This loop IGNORES the loop_enabled flag.
 */
size_t			anim_loop_pingpong(t_anim_sprite *sprite);

#endif