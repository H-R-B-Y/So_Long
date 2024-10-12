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

// Need libft ../../../../../../../../libft/libft.h Lol
# include "../../lib/libft/libft.h"

// for malloc and free
#include <stdlib.h>

// for read
#include <unistd.h>

# define MAP_WALL '#'
# define MAP_EMPTY '0'
# define MAP_PLAYER 'P'
# define MAP_EXIT 'E'
# define MAP_COLLECTIBLE 'C'
# define MAP_CHARSET "#0PEC"

/*
Map proto is a 3D array of char
	The first dimension is the height of the map
	The second dimension is the width of the map
To access a character at x, y in the map proto:
	map_proto[y][x]
*/
typedef char **t_map_proto;

/*
Map is a struct containing the following fields:
@width: width of the map
@height: height of the map
@map: 2D array of characters representing the map
*/
typedef struct s_map
{
	size_t		width;
	size_t		height;
	size_t		player[2];
	size_t		exit[2];
	char		*map;
	
}	t_map;

//	Prototypes

/*
Reads the map proto from a file descriptor.
@fd: file descriptor to read from
@returns: map proto (2D char array), NULL if malloc fails or read fails.
*/
t_map_proto		_map_proto_read(int fd); // should be static

/*
Frees the map proto.
@map_proto: map proto to free
*/
void			_map_proto_free(t_map_proto map_proto); // should be static

/*
Validates the map proto.
@map_proto: map proto to validate
@returns: 1 if valid, 0 if invalid.
*/
int				_map_proto_validate(t_map_proto map_proto, size_t size[2]); // should be static

// MAP VALIDATE SUB FUNCTIONS:
int		map_all_same_size(t_map_proto map_proto, size_t size[2]);
int		map_has_required(t_map_proto map_proto, int *flags, size_t size[2]);
int		map_surrounded(t_map_proto map_proto, size_t size[2]);

/*
Parses the map proto into a map struct.
Note: The map struct should contain a copy of the map proto.
Note: The map struct will not be freed on error.
@map_proto: map proto to parse
@returns: map struct, NULL if error.
*/
t_map			*_map_parse_proto(t_map_proto map_proto); // should be static

// These are the only function that should be exposed to the user

/*
Parses the map from a file descriptor.
@fd: file descriptor to read from
@returns: map struct, NULL if error.
*/
t_map			map_parse(int fd);

/*
Frees the map.
@map: map to free
*/
void			map_free(t_map map);

#endif