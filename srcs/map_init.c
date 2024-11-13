/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:11:15 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/13 13:36:42 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_map(char **map)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			write(1, &map[y][x], 1);
			x++;	
		}
		y++;
	}
}

static int	map_rows(char *arg)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	line = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
        return (-1);
	line = get_next_line(fd);
	// printf("\nline here: %s\n fd: %d\n", line, fd);
	while (line)
	{
		// printf("\ngnl line: %s\n fd: %d\n", line, fd);

		free(line);
		line = get_next_line(fd);
		if (line)
		{
			// if (line[0] == '\n')
            // {
            //     write(2, "Error: Extra line at bottom\n", 29);
			// 	// free(line);
            //     continue;        
            // }
		}
		i++;
	}
	free (line);
	close (fd);
	return (i);
}

static char	**map_to_str(t_map_data *game, char *argv)
{
	int			fd;
	int			i;

	fd = 0;
	i = 0;
	game->info = (char **)ft_calloc((size_t)game->rows + 1, sizeof(char *));
	if (!game->info)
        handle_error(EXIT_MAP_INIT_CALLOC_FAIL, game);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		handle_error(EXIT_FD_OPEN_ERROR, game);
	while (game->rows > i)
	{
		game->info[i] = get_next_line(fd);
		i++;
	}
	close (fd);
	print_map(game->info);
	return (game->info);
}

char	**find_map(char	**game)
{
	return(game);
}

static int	map_parse(char **argv, t_map_data	*game)
{
	char	**maze_map;

	// printf("\nbefore maprows\n");
	game->rows = map_rows(argv[1]);
   	// printf("\nafter maprows\n");
    if (game->rows == -1)
    {
		printf("\ninside here\n");
	    game->rows = 0;
        return (1);
    }
	game->info = map_to_str(game, argv[1]);
	maze_map = find_map(game->info);
	(void)argv;
    return (0);
}



int	parse_args(char **argv, t_map_data	*game)
{
	(void)game;
	if (!argv)
		return (EXIT_ARG_COUNT_ERROR);
	if ((ft_strlen(argv[1]) <= 4) || (argv[1][ft_strlen(argv[1]) - 5] == '/')
		|| (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0))
		return (EXIT_ARG_NAME_ERROR);
	if (map_parse(argv, game))
		return (EXIT_MAP_INIT_ERROR);
	else
	{
		printf("\nNICE FILE!\n");
		return (1);
	}
}