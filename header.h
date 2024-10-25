/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:44:21 by jbremser          #+#    #+#             */
/*   Updated: 2024/10/25 16:09:46 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <unistd.h>

typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
   	EXIT_INVALID_ARGS = 201,
}	t_error;

typedef struct s_map_data
{
    char    **map;
    char    **copy;
    
}   t_map_data;

/* ************************************************************************** */
/*									error_handling							  */
/* ************************************************************************** */
int	handle_error(int errno, t_map_data *game);

#endif