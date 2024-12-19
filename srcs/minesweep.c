/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:17:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/12/18 15:24:28 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	sweep(t_map_data *game, int y, int x)
{  
	if (!(game->map[y][x + 1]) ||
		!(game->map[y + 1][x + 1]) ||
		!(game->map[y + 1][x]) ||
		!(game->map[y - 1][x - 1]) ||
		!(game->map[y][x - 1]) ||
		!(game->map[y - 1][x - 1]) ||
		!(game->map[y + 1][x]) ||
		!(game->map[y - 1][x + 1]) ||
		!(game->map[y + 1][x + 1]))
		{
			printf("Sweep failed, invalid map!\n");
			return (1);
		}
	else
		return (0);
}
/* check every 0 and the surrounding area to make sure they exist and not 
blank space and thus invalid map */
int minesweep(t_map_data *game)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	printf("b4 minesweep\n");
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == '0')
			{
				if (sweep(game, y, x))
					return (1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	printf("after minesweep\n");
	return (0);
}
