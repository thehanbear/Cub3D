/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:51:35 by jbremser          #+#    #+#             */
/*   Updated: 2024/12/18 15:58:30 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int main(int argc, char **argv)
{
	t_map_data  *game;

	game = NULL;
	// ft_memset(game, 0, sizeof(t_map_data));
	game = ft_calloc(1, sizeof(t_map_data));
	if (argc != 2 || !argv)
		return (handle_error(EXIT_ARG_COUNT_ERROR, game));
	if (!handle_error(parse_args(argv, game), game))
		return (1);
	printf("\nPARSING COMPLETE!\n");
	if (!handle_error(init_game(game), game))
		return (1);
	start_game(game);
	if (game)
		free_game_struct(game);
	return (0);

}
