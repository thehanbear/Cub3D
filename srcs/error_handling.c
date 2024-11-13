/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:00:30 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/13 13:34:58 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_array(char **str)
{
	int	y;

	y = 0;
	while (str[y])
		free(str[y++]);
	free(str);
}

void	free_game_struct(t_map_data	*game)
{
	if (game->copy)
		free_array(game->copy);
	if (game->info)
		free_array(game->info);
	if (game)
		free(game);
}

void	map_free_error(int errno, t_map_data	*game)
{
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL)
		printf("Error: Calloc fail\n");
	if (errno == EXIT_FD_OPEN_ERROR)
		printf("FD NO OPEN!\n");
	if (game)
		free_game_struct(game);
	exit(2);
}

int	handle_error(int errno, t_map_data *game)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
   		write(2, "Invalid amount of Args\n", 24);
	if (errno == EXIT_INVALID_ARGS)
   		write(2, "Invalid Arguments\n", 19);
	if (errno == EXIT_ARG_NAME_ERROR)
   		write(2, "Invalid File Names\n", 20);
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL)
		map_free_error(errno, game);
	if (errno == EXIT_FD_OPEN_ERROR)
		map_free_error(errno, game);
	if (game)
		free_game_struct(game);
	if (errno == 0)
		return (0);
	else
		return (1);	
}