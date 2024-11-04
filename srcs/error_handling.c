/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:00:30 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/04 17:18:46 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	map_free_error(t_map_data	*game)
{
	printf("Error: Calloc fail\n");
}

int	handle_error(int errno, t_map_data *game)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
   		(void)!write(2, "Invalid amount of Args\n", 24);
	if (errno == EXIT_INVALID_ARGS)
   		(void)!write(2, "Invalid Arguments\n", 19);
	if (errno == EXIT_ARG_NAME_ERROR)
   		(void)!write(2, "Invalid File Names\n", 20);
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL)
		map_free_error(game);	
	(void)game;
	if (errno == 0)
		return (0);
	else
		return (1);	
}