/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:17:50 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/20 13:37:59 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	sweep(t_map_data *game, int y, int x);
static int	if_empty(t_map_data *game, int y, int x);
int			minesweep(t_map_data *game);

static int if_empty(t_map_data *game, int y, int x)
{
	if ((game->map[y][x] == '\n') || (game->map[y][x] == '\t') ||
		(game->map[y][x] == ' ') || !(game->map[y][x]))
	{
		printf("y.x.: %d, %d \n minesweep failed\n", y, x);
		return (1);
	}
	else
		return (0);
}

/*(game->map[y][x] != '0') || (game->map[y][x] != '1')*/
// static int if_empty(t_map_data *game, int y, int x)
// {
// 	if (game->map[y][x] != '0')
// 	{
// 		printf("y.x.: %d, %d \n minesweep failed 0 not found\n", y, x);
// 		return (1);
// 	}
// 	if (game->map[y][x] != '1')
// 		{
// 		printf("y.x.: %d, %d \n minesweep failed 1 not found\n", y, x);
// 		return (1);
// 	}
// 	if (game->map[y][x] == '\n')
// 		{
// 		printf("y.x.: %d, %d \n minesweep failed newline found\n", y, x);
// 		return (1);
// 	}
// 	if (game->map[y][x] == '\t')
// 	{
// 		printf("y.x.: %d, %d \n minesweep failed space found\n", y, x);
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

/* checks every spot around playable spaces*/
static int	sweep(t_map_data *game, int y, int x)
{
	if (if_empty(game, y, x + 1) ||
		if_empty(game, y + 1, x + 1) ||
		if_empty(game, y + 1, x) ||
		if_empty(game, y - 1, x - 1) ||
		if_empty(game, y, x - 1) ||
		if_empty(game, y - 1, x - 1) ||
		if_empty(game, y + 1, x) ||
		if_empty(game, y - 1, x + 1) ||
		if_empty(game, y + 1, x + 1))
	{
		write(2, "Sweep failed, invalid map!\n", 27);
		return (1);
	}
	else
		return (0);
}

/* check every 0 and the surrounding area to make sure they exist and not
blank space and thus invalid map */
int	minesweep(t_map_data *game)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	printf("Inside Minesweep\n");
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
	return (0);
}
