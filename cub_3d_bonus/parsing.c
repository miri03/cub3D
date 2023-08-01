/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:05:01 by meharit           #+#    #+#             */
/*   Updated: 2023/08/01 19:31:55 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_map(char *map)
{
	int	len;
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(MAG, 2);
		write(2, "error\n", 6);
		perror("");
		exit(1);
	}
	len = ft_strlen(map);
	if (len <= 4 || map[len - 5] == '/' || map[len - 4] != '.'
		|| map[len - 3] != 'c' || map[len - 2] != 'u' || map[len - 1] != 'b')
		error_mess("bad extention\n");
	return (fd);
}

void	init_pars(t_mlx *m)
{
	m->map.tile = 50;
	m->t[0].path = NULL;
	m->t[1].path = NULL;
	m->t[2].path = NULL;
	m->t[3].path = NULL;
	m->map.floor_color = -1;
	m->map.sky_color = -1;
	m->map.x_elements_nb = 0;
	m->map.y_elements_nb = 0;
	m->p.angle = -1;
}

int	n_line(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

void	map_starting(int fd, int start)
{
	char	*line;
	int		index;

	index = 0;
	line = get_next_line(fd);
	while (line && index + 1 < start)
	{
		if (index + 1 < start)
			free(line);
		line = get_next_line(fd);
		index++;
	}
	free(line);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	t_mlx	*m;
// 	int		start;

// 	if (argc == 2)
// 	{
// 		m = malloc(sizeof(t_mlx));
// 		init(m);
// 		fd = open_map(argv[1]);
// 		start = textures(fd, m);
// 		height_len(fd, m);
// 		if (!m->t[0].path || !m->t[1].path || !m->t[2].path || !m->t[3].path
// 			|| m->map.sky_color == -1 || m->map.floor_color == -1)
// 			error_mess("identifier missing\n");
// 		map(argv[1], start, m);
// 		m->map.x_elements_nb = max_len(argv[1], start);
// 	}
// 	else
// 		error_mess("no\n");
// }
