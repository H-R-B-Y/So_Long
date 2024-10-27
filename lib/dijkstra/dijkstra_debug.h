/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_debug.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-14 17:46:47 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-14 17:46:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIJKSTRA_DEBUG_H
# define DIJKSTRA_DEBUG_H

# ifndef PRINT_DELAY
#  define PRINT_DELAY 100000
# endif

# include "dijkstra.h"

/**
 * @brief Debug function to print the cost map
 * @param cost_map map of costs
 * @param map map to use, must have is valid function
 * @param highlight position to highlight
 * @param colour function to get colour of cell
 * 
 * This function is only used when compiled with debug.
 */
void	debug_print_dijkstra(\
			t_dj_map *map,
			t_dj_position highlight,
			int (*colour)(void *, t_dj_position)
			);

#endif