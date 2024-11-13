/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:44:21 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/13 13:33:33 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
	EXIT_INVALID_ARGS = 201,
	EXIT_ARG_NAME_ERROR = 202,
	EXIT_MAP_INIT_ERROR = 203,
	EXIT_MAP_INIT_CALLOC_FAIL = 204,
	EXIT_FD_OPEN_ERROR = 205,
}	t_error;

typedef struct s_map_data
{
	char    **info;
	char	**maze_map;
	char    **copy;
	int		rows;

}   t_map_data;

/* ************************************************************************** */
/*									error_handling							  */
/* ************************************************************************** */
int	handle_error(int errno, t_map_data *game);

/* ************************************************************************** */
/*									map_init								  */
/* ************************************************************************** */
int	parse_args(char **argv, t_map_data	*game);


#endif