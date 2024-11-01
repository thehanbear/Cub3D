/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:51:35 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/01 17:13:52 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	parse_args(char **argv, t_map_data	*game)
{
	(void)game;
	if (!argv)
		return (handle_error(EXIT_ARG_COUNT_ERROR, game));
	if ((ft_strlen(argv[1]) <= 4) || (argv[1][ft_strlen(argv[1]) - 5] == '/')
		|| (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0))
		return (handle_error(EXIT_ARG_NAME_ERROR, game));
	// if (())	
	else
	{
		printf("NICE FILE!\n");
		return (1);
	}

}

int main(int argc, char **argv)
{
	t_map_data  *game;

	game = NULL;
	if (argc != 2 || !argv)
		return (handle_error(EXIT_ARG_COUNT_ERROR, game));
	if (handle_error(parse_args(argv, game), game))
		return (1);

	
}