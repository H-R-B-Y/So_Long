/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 16:05:30 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 16:05:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIJKSTRA_H
# define DIJKSTRA_H

# include "include/libft.h"

# include <stdlib.h>

typedef struct s_dj_position
{
	size_t	y;
	size_t	x;
}	t_dj_position;

typedef struct s_cell
{
	t_dj_position	pos;
	int				cost;
	int				visited;
}	t_cell;

typedef t_list	t_queue;
typedef t_cell	**t_cost_map;

/**
 * @brief Map structure for Dijkstra's algorithm
 * 
 * This structure is used to store the map for Dijkstra's algorithm.
 * The map must contain a width and height, 
 * a start position and an is valid function.
 * The map may also contain an end position and a get type function.
 * The cost map will be populated once Dijkstra's algorithm is run.
 */
typedef struct s_dj_map
{
	size_t			width;
	size_t			height;
	void			*map;
	t_dj_position	start;
	int				has_end;
	t_dj_position	end;
	int				(*is_valid)(void *, t_dj_position);
	int				(*get_type)(void *, t_dj_position);
	t_cost_map		cost_map;
}	t_dj_map;

/**
 * @brief Initialize cost map with -1 cost and 0 visited
 * @param map map to initialize, must contain width and height
 * @return 1 on success, 0 on failure
 */
int		init_cost_map(t_dj_map *map);

/**
 * @brief Enqueue a cell with a cost
 * @param queue queue to add to
 * @param cell cell to add
 * @param cost cost of cell
 */
void	dj_enqueue(t_queue **queue, t_cell *cell, int cost);

/**
 * @brief Dequeue a cell from the queue
 * @param queue queue to dequeue from
 * @return dequeued cell
 */
t_cell	*dj_dequeue(t_queue **queue);

/**
 * @brief Runs Dijkstra's algorithm on the map to produce cost map
 * @param queue queue to use
 * @param map map to use, must have is valid function
 * 
 * This function will run Dijkstra's algorithm on the
 * map to produce a cost map.
 * The function returns when either the end
 * cell is reached or the queue is empty.
 */
void	dijkstra(t_queue **queue, t_dj_map *map);

/**
 * @brief Clean up cost map
 * @param map map to clean up
 */
void	dijkstra_clean_up(t_dj_map *map);

/**
 * @brief Wrapper function to perform dijkstra
 * @param map map to use, must have is valid function
 * @return 1 on success, 0 on failure
 * 
 * This function will initialize the cost map, enqueue the start cell
 * and call dijkstra to calculate the entire cost map.
 */
int		perform_dijkstra(t_dj_map *map);

#endif