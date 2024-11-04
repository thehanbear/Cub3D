/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:11:15 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/04 17:13:31 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
		// error_msg_exit("Error: Where Map? FD failed\n", game);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			if (line[0] == '\n')
            {
                write(2, "Error: Extra line at bottom\n", 29);
                exit (2);        
            }
		}
		i++;
	}
	free (line);
	close (fd);
	return (i);
}

static char	**map_to_str(t_map_data *game, char *argv)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	game->map = (char **)ft_calloc((size_t)game->rows + 1, sizeof(char *));
	if (!game->map)
        handle_error(CALLOC_FAIL, game);
		// error_exit_array("Error: Calloc fail\n", game, game->map);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_exit_array("Error: FD open fail\n", game, game->map);
	while (game->rows > i)
	{
		game->map[i] = get_next_line(fd);
		i++;
	}
	close (fd);
	return (game->map);
}

static int	map_init(char **argv, t_map_data	*game)
{
	game->rows = map_rows(argv[1]);
    if (game->rows == -1)
    {
        game->rows = 0;
        return (1);
    }
    game->map = map_to_str(game, argv[1]);
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
	if (map_init(argv, game))
		return (EXIT_MAP_INIT_ERROR);
	else
	{
		printf("NICE FILE!\n");
		return (1);
	}

}