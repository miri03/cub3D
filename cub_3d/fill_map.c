/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:31:35 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 15:04:10 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	start_map(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '0' || line[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

char	*put_line(char *line, t_mlx *m)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(sizeof(char) * (m->map.x_elements_nb + 1));
	while (line[i] || m->map.x_elements_nb > i)
	{
		if (line[i] == ' ' || line[i] == '\t')
			result[i] = 'X';
		else if (line[i] == '\n')
		{
			while (i < m->map.x_elements_nb)
			{
				result[i] = 'X';
				i++;
			}
			result[i] = '\0';
			break ;
		}
		else
			result[i] = put_line_uti(line[i]);
		i++;
	}
	return (result);
}

char	*last(char *line, t_mlx *m)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(sizeof(char) * (m->map.x_elements_nb + 1));
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			result[i] = 'X';
		else if (line[i] == '\n')
			error_mess("empty line in the map\n");
		else
			result[i] = line[i];
		i++;
	}
	while (i < m->map.x_elements_nb)
	{
		result[i] = 'X';
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	fill_map(int fd, t_mlx *m)
{
	char	*line;
	int		i;

	i = 0;
	m->map.map = (char **)malloc(sizeof(char *) * (m->map.y_elements_nb + 1));
	line = get_next_line(fd);
	m->map.map[i] = put_line(line, m);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
		if (m->map.y_elements_nb == i + 1)
		{
			m->map.map[i] = last(line, m);
			m->map.map[i + 1] = NULL;
			free(line);
			break ;
		}
		else if (line)
			m->map.map[i] = put_line(line, m);
	}
	// i=0;
	// while (m->map.map[i])
	// {
	// 	printf("%s\n", m->map.map[i]);
	// 	i++;
	// }
}

void	map(char *file_path, int start, t_mlx *m)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_mess("open() failed\n");
	map_starting(fd, start);
	fill_map(fd, m);
	pars_map(m->map.map, m);
}
