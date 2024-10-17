/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-17 13:31:53 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-17 13:31:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "../../include/MLX42.h"
# include "../../include/libft.h"

# include "../../include/map_parse.h"

# include "../../include/anim_engine.h"

# include "../utils/utils.h"


/*

██╗   ██╗██╗███████╗██╗    ██╗      
██║   ██║██║██╔════╝██║    ██║      
██║   ██║██║█████╗  ██║ █╗ ██║█████╗
╚██╗ ██╔╝██║██╔══╝  ██║███╗██║╚════╝
 ╚████╔╝ ██║███████╗╚███╔███╔╝      
  ╚═══╝  ╚═╝╚══════╝ ╚══╝╚══╝       
                                    
██████╗  ██████╗ ██████╗ ████████╗  
██╔══██╗██╔═══██╗██╔══██╗╚══██╔══╝  
██████╔╝██║   ██║██████╔╝   ██║     
██╔═══╝ ██║   ██║██╔══██╗   ██║     
██║     ╚██████╔╝██║  ██║   ██║     
╚═╝      ╚═════╝ ╚═╝  ╚═╝   ╚═╝     
                                    
 */

// Aspect ratio 16:9
# define VIEWPORT_WIDTH (16 * 2)
# define VIEWPORT_HEIGHT (9 * 2)

typedef struct s_viewport t_viewport;

struct s_viewport
{
	mlx_t		*mlx;
	size_t		tile_size[2];
	t_position	view_offset;

	t_position	viewport_size;

	int			map_smaller;
	t_position	map_offset;

	t_map		*map;

	mlx_image_t	*bg_img;
	char		*bg_path;
	mlx_image_t	*fg_img;
	char		*fg_path;
	int			**fg_matrix;

	t_list		*objects;
	int			need_redraw;

};

/**
 * @brief Initialize the background
 * @param view viewport to initialize the background for
 * @param path path to the background image
 * @return pointer to the background image if successful, 0 if not
 */
mlx_image_t	*init_background(t_viewport *view, char *path);

/**
 * @brief Initialize the foreground
 * @param view viewport to initialize the foreground for
 * @param path path to the foreground image
 * @return pointer to the foreground image if successful, 0 if not
 * This will draw the foreground on top of the background
 */
mlx_image_t	*init_foreground(t_viewport *view, char *path);

/**
 * @brief Initialize the viewport
 * @param mlx MLX42 instance
 * @param map map to display
 * @param textures array of paths to textures
 * @return pointer to the viewport if successful, 0 if not
 */
t_viewport	*init_viewport(mlx_t *mlx, t_map *map, char *textures[2]);

/**
 * @brief Destroy the viewport
 * @param view viewport to destroy
 */
void		destroy_viewport(t_viewport *view);

/**
 * @brief Draw the viewport
 * @param view viewport to draw
 * @return 1 if successful, 0 if not
 */
int			draw_viewport(t_viewport *view);

/**
 * @brief Calculate the viewport size
 * @param view viewport to calculate the size for
 * @param size new viewport size
 */
int			calc_view_size(t_viewport *view, t_position size);

/*
██╗███╗   ██╗███████╗████████╗      
██║████╗  ██║██╔════╝╚══██╔══╝      
██║██╔██╗ ██║███████╗   ██║         
██║██║╚██╗██║╚════██║   ██║         
██║██║ ╚████║███████║   ██║         
╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝         
                                    
███╗   ███╗████████╗██████╗ ██╗  ██╗
████╗ ████║╚══██╔══╝██╔══██╗╚██╗██╔╝
██╔████╔██║   ██║   ██████╔╝ ╚███╔╝ 
██║╚██╔╝██║   ██║   ██╔══██╗ ██╔██╗ 
██║ ╚═╝ ██║   ██║   ██║  ██║██╔╝ ██╗
╚═╝     ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝
                                    
*/

/**
 * @brief Move the viewport in the given direction
 * @param view viewport to move
 * @param direction direction to move in
 * @note Check for walls before this point
 * @note Check players current offset before this point (offset needs to be reduced to 0 before moving)
 * @note Direction should be normalized
 */
void			move_viewport(t_viewport view, t_position direction);

void		move_matrix(t_viewport *view,
				mlx_image_t *parent,
				int **instance_matrix,
				int depth);
void		free_instance_matrix(int **instances, t_position size);
int			**create_instance_matrix(mlx_t *mlx,
				mlx_image_t	*img,
				t_position	size);

typedef struct s_view_obj t_view_obj;

/*
██╗   ██╗██╗███████╗██╗    ██╗   
██║   ██║██║██╔════╝██║    ██║   
██║   ██║██║█████╗  ██║ █╗ ██║   
╚██╗ ██╔╝██║██╔══╝  ██║███╗██║   
 ╚████╔╝ ██║███████╗╚███╔███╔╝   
  ╚═══╝  ╚═╝╚══════╝ ╚══╝╚══╝    
                                 
 ██████╗ ██████╗      ██╗███████╗
██╔═══██╗██╔══██╗     ██║██╔════╝
██║   ██║██████╔╝     ██║███████╗
██║   ██║██╔══██╗██   ██║╚════██║
╚██████╔╝██████╔╝╚█████╔╝███████║
 ╚═════╝ ╚═════╝  ╚════╝ ╚══════╝
                                 
*/

typedef int (*t_view_obj_enable)(t_view_obj *obj, struct s_viewport *view);
typedef int (*t_view_obj_disable)(t_view_obj *obj, struct s_viewport *view);

/**
 * @brief Structure to hold the object to be displayed on the viewport
 * @param pos Position on the map
 * @param data Pointer to the object data
 * @param enable Function to enable the object
 * @param disable Function to disable the object
 * @param destroy Function to destroy the object (Default is free)
 */
struct s_view_obj
{
	t_position			pos; // Position on the map
	void				*data;
	t_view_obj_enable	enable;
	t_view_obj_disable	disable;
	void				(*destroy)(void *obj);
};

/**
 * @brief Create a new viewport object
 * @param pos Position on the map
 * @param obj Pointer to the object data
 * @param enable Function to enable the object
 * @param disable Function to disable the object
 * @return Pointer to the new object if successful, 0 if not
 */
t_view_obj	*create_viewport_obj(t_position pos,
				void *obj,
				t_view_obj_enable enable,
				t_view_obj_disable disable);

/**
 * @brief Add an object to the viewport
 * @param view Pointer to the viewport
 * @param obj Pointer to the object to add
 * @return 1 if successful, 0 if not
 * @note The object will be added to the end of the list
 */
int			view_add_obj(t_viewport *view, t_view_obj *obj);

/**
 * @warning Make sure obj has the correct destroy function
 * @brief Delete an object from the viewport
 * @param view Pointer to the viewport
 * @param obj Pointer to the object to delete
 * @return 1 if successful, 0 if not
 * @note The object will be deleted from the list
 * @note The object and it's data will be destroyed
 */
int			view_del_obj(t_viewport *view, t_view_obj *obj);

/**
 * @brief Draw objects that are in the viewport
 * @param view Pointer to the viewport
 * @return 1 if successful, 0 if not
 */
int			viewport_draw_objects(t_viewport *view);

#endif 