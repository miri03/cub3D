/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_uti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:18:43 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 14:52:09 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	error_mess(char *msg)
{
	ft_putstr_fd(MAG, 2);
	write(2, "error\n", 6);
	while (*msg)
	{
		write(2, msg, 1);
		msg++;
	}
	ft_putstr_fd(RESET, 2);
	system("leaks cub3D");
	exit(1);
}

int	empty(char *line)
{
	while (line && *line)
	{
		if ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		else
			return (0);
	}
	return (1);
}

void	height_len(int fd, t_mlx *m)
{
	char	*line;

	m->map.y_elements_nb = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (empty(line))
			error_mess("!\n");
		if ((int)ft_strlen(line) - n_line(line) > m->map.x_elements_nb)
			m->map.x_elements_nb = ft_strlen(line) - n_line(line);
		m->map.y_elements_nb++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	max_len_uti(char *line, int *max)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != '\n')
	{
		i++;
		len++;
	}
	if (len > *max)
		*max = len;
}

int	max_len(char *file_path, int start)
{
	char	*line;
	int		fd;
	int		max;

	max = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_mess("open() failed\n");
	map_starting(fd, start);
	line = get_next_line(fd);
	while (line)
	{
		max_len_uti(line, &max);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (max);
}
