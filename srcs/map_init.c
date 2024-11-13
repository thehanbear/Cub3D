/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:11:15 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/13 17:56:47 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_map(char **map)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	write(1, "\n", 1);
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
	write(1, "\n", 1);
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
	return (game->info);
}

char	*find_asset(t_map_data	*game, char	*arg)
{
	int y = 0;
	int x = 0;

	while (game->info[y])
	{
		if (!ft_strncmp(&game->info[y][x], arg, ft_strlen(arg)))
		{
			x = ft_strlen(arg) - 1;
			while(!ft_strncmp(&game->info[y][x], " ", 1))
				x++;
			return (ft_strdup(&game->info[y][x]));
		}
		y++;
	}
	return (NULL);
}
			// game->map = (char **)ft_calloc(game->rows + 1, sizeof(char *));
			// 	if (!game->map)
			// 		handle_error(EXIT_MAP_INIT_CALLOC_FAIL, game);

int find_no_map(t_map_data *game)
{
    int y = 0;
    int x = 0;

    while (game->info[y])
    {
        x = 0;
        while (game->info[y][x] == ' ')
            x++;
        if (game->info[y][x] == '1')
            return (0);
        y++;
    }
    return (1);
}

void find_ones(t_map_data *game)
{
    int y = 0;
    int a = 0;
    int x = 0;
	if (find_no_map(game))
		handle_error(EXIT_NO_MAP, game);
    while (game->info[y])
    {
        x = 0;
        while (game->info[y][x] && game->info[y][x] == ' ')
            x++;
        if (game->info[y][x] && game->info[y][x] == '1')
        {
            game->map = (char **)ft_calloc((game->rows - y + 1), sizeof(char *));
            if (!game->map)
                handle_error(EXIT_MAP_INIT_CALLOC_FAIL, game);
            while (game->info[y])
            {
                game->map[a] = ft_strdup(game->info[y]);
                a++;
                y++;
            }
            game->map_rows = a;
        }
        y++;
    }
} 

// void	find_ones(t_map_data	*game)
// {
// 	int y = 0;
// 	int a = 0;
// 	int x = 0;
	
// 	while (game->info[y])
// 	{
// 		while (game->info[y][x])
// 		{
// 			if (!ft_strncmp(&game->info[y][x], " ", 1))
// 				x++;

// 		}
// 		if (!ft_strncmp(&game->info[y][x], "1", 1))
// 			break ;
// 		y++;
// 	}
// 	game->map_rows = game->rows - y;
// 	game->map = ft_calloc((game->map_rows), sizeof(char *));
// 	while (a < game->map_rows)
// 		game->map[a++] = ft_strdup(game->info[y++]);
// }

void	print_info(t_map_data *game)
{
	printf("game->info map:\n");
	print_map(game->info);
	printf("game->map map:\n");
	ft_printf("n_wall: %s\n", game->n_wall_asset);
	ft_printf("s_wall: %s\n", game->s_wall_asset);
	ft_printf("w_wall: %s\n", game->w_wall_asset);
	ft_printf("e_wall: %s\n", game->e_wall_asset);
	ft_printf("floor: %s\n", game->floor_color);
	ft_printf("ceiling: %s\n", game->ceiling_color);
	ft_printf("rows: %d\n", game->rows);
	ft_printf("map rows: %d\n", game->map_rows);
	print_map(game->map);


}

void	find_map(t_map_data	*game)
{
	game->n_wall_asset = find_asset(game, "NO ");
	game->s_wall_asset = find_asset(game, "SO ");
	game->w_wall_asset = find_asset(game, "WE ");
	game->e_wall_asset = find_asset(game, "EA ");
	game->floor_color = find_asset(game, "F ");
	game->ceiling_color = find_asset(game, "C ");
	//malloc map here
	find_ones(game);
	print_info(game);
	// (void)(game);
}

static int	map_parse(char **argv, t_map_data	*game)
{
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
	find_map(game);
	clean_info_struct(game);
	printf("after clean_info_struct\n");
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
		// printf("\nNICE FILE!\n");
		return (1);
	}
}