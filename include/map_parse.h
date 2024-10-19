/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:25:58 by hbreeze           #+#    #+#             */
/*   Updated: 2024/10/10 14:54:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSE_H
# define MAP_PARSE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef MAP_KEY
#  define MAP_KEY "#0PEC"
#  define MAP_WALL MAP_KEY[0]
#  define MAP_EMPT MAP_KEY[1]
#  define MAP_PLAY MAP_KEY[2]
#  define MAP_EXIT MAP_KEY[3]
#  define MAP_COIN MAP_KEY[4]
#endif

/**
 * @brief Type definition for a map_proto
 * 
 * A map_proto is a 2D char array (null terminated)
 */
typedef char	**t_map_proto;

/**
 * @brief Struct containing a position
 * @param y y coordinate
 * @param x x coordinate
 */
typedef struct s_position
{
	size_t	y;
	size_t	x;
}	t_position;

/**
 * @struct s_map
 * @brief Struct containing a map
 * @param width width of the map
 * @param height height of the map
 * @param player position of the player
 * @param exit position of the exit
 * @param coin_count number of coins in the map
 * @param coins list of coin positions
 * @param map 2D char array containing the map
 * @param map[y][x] is the character at position x, y
 */
typedef struct s_map t_map;
struct s_map
{
	size_t		width;
	size_t		height;
	t_position	size;
	t_position	player;
	t_position	exit;
	size_t		coin_count;
	t_list		*coins;
	t_map_proto	map;
};

//	Prototypes

/**
 * @brief Reads a map from a file descriptor into a map_proto
 * @param fd file descriptor to read from
 * @return t_map_proto containing the map
 * 
 * The map proto is a 2D char array (null terminated)
 */
t_map_proto		map_proto_read(int fd);

/**
 * @brief Frees a map_proto
 * @param map_proto map_proto to free
 */
void			map_proto_free(t_map_proto map_proto);

/**
 * @brief Parses a map_proto into a t_map
 * @param map_proto map_proto to parse
 * @return t_map containing the map
 */
t_map			*create_map(t_map_proto map_proto);

/**
 * @brief Frees a t_map
 * @param map t_map to free
 */
void			free_map(t_map *map);

#endif