/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:17:50 by jbremser          #+#    #+#             */
/*   Updated: 2025/02/26 12:56:57 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	sweep(t_map_data *game, int y, int x);
static int	if_empty(t_map_data *game, int y, int x);
int			minesweep(t_map_data *game);
int			check_line(char *line);
int			check_info(t_map_data *game);

static int	if_empty(t_map_data *game, int y, int x)
{
	if ((game->map[y][x]) == '\0')
	{
		
		printf("x: %d, y: %d \n here\n", x, y);
		return (1);
	}
	else if ((game->map[y][x] == '\n')
		|| (game->map[y][x] == '\t') || (game->map[y][x] == ' '))
		{
			printf("there\n");
		return (1);
		}
	else
		return (0);
}

/* checks every spot around playable spaces*/
static int	sweep(t_map_data *game, int y, int x)
{
	if (if_empty(game, y, x + 1)
		|| if_empty(game, y + 1, x + 1)
		|| if_empty(game, y + 1, x)
		|| if_empty(game, y - 1, x - 1)
		|| if_empty(game, y, x - 1)
		|| if_empty(game, y - 1, x - 1)
		|| if_empty(game, y + 1, x)
		|| if_empty(game, y - 1, x + 1)
		|| if_empty(game, y + 1, x + 1))
	{
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

int	check_line(char *line)
{
	int	x;

	x = 0;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (0);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] == '1' || line[x] == '\n')
		return (0);
	else
		return (1);
}

int	check_info(t_map_data	*game)
{
	int	y;

	y = 0;
	while (game->info[y])
	{
		if (check_line(game->info[y]))
			return (1);
		y++;
	}
	return (0);
}
