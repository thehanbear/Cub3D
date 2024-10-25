/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:51:35 by jbremser          #+#    #+#             */
/*   Updated: 2024/10/25 16:13:00 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	parse_args(char **argv, t_map_data	*game)
{
	(void)game;
	if (argv)
		return (0);
	else
		return (1);
}

int main(int argc, char **argv)
{
	t_map_data  *game;

	game = NULL;
	if (argc != 2)
		return (handle_error(EXIT_ARG_COUNT_ERROR, game));
	if (parse_args(argv, game))
		return (handle_error(EXIT_INVALID_ARGS, game));		
}