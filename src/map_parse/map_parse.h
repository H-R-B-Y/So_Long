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

// Need libft ../../../../../../../../libft/libft.h LoL
# include "../../lib/libft/libft.h"

// for malloc and free
#include <stdlib.h>

// for read
#include <unistd.h>

# define MAP_WALL '#'
# define MAP_EMPT '0'
# define MAP_PLAY 'P'
# define MAP_EXIT 'E'
# define MAP_COIN 'C'

typedef char **t_map_proto;

# ifndef T_POSITION
#  define T_POSITION

typedef struct s_position
{
	size_t y;
	size_t x;
}	t_position;

# endif


typedef struct s_map
{
	size_t		width;
	size_t		height;
	t_position	player;
	t_position	exit;
	size_t 		coin_count;
	t_list		*coins;
	t_map_proto		map;
}	t_map;

//	Prototypes

t_map_proto		map_proto_read(int fd);
void			map_proto_free(t_map_proto map_proto);
t_map			*create_map(t_map_proto map_proto);
void			free_map(t_map *map);


#endif