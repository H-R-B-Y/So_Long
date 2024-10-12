/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_proto_read_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:01:26 by hbreeze           #+#    #+#             */
/*   Updated: 2024/10/01 19:17:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map_parse_internal.c"
#include "../map_parse.h"


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
	int fd = open("testmap", O_RDONLY);

	t_map_proto map_proto = _map_proto_read(fd);
}