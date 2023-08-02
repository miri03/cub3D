/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:15:00 by meharit           #+#    #+#             */
/*   Updated: 2023/08/02 12:14:32 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	f_s(int	*floor, int *sky, t_mlx *m, char *line)
{
	if (*floor == TRUE)
	{
		pars_color(line, m, 0);
		*floor = FALSE;
	}
	if (*sky == TRUE)
	{
		pars_color(line, m, 1);
		*sky = FALSE;
	}
}

int	textures(int fd, t_mlx *m)
{
	char	*line;
	int		sky;
	int		floor;
	int		index;

	index = 0;
	sky = -1;
	floor = -1;
	line = get_next_line(fd);
	while (line)
	{
		m->map.x_elements_nb = ft_strlen(line) - n_line(line);
		if (!check_line(line, m, &sky, &floor))
			return (index);
		if (floor == TRUE || sky == TRUE)
			f_s(&floor, &sky, m, line);
		free(line);
		line = get_next_line(fd);
		index++;
	}
	free(line);
	error_mess("map missing\n");
	return (0);
}

int	check_line(char *line, t_mlx *m, int *sky, int *floor)
{
	char	**result;
	char	**tmp;

	tmp = ft_split(line, '\n');
	if (!tmp[0])
	{
		free_tab(tmp);
		return (1);
	}
	result = ft_space_split(tmp[0], ' ', '\t');
	if (result[0] && start_map(result[0]))
	{
		free_tab(tmp);
		free_tab(result);
		free(line);
		return (0);
	}
	check_ident(result, m, sky, floor);
	free_tab(result);
	free_tab(tmp);
	return (1);
}

void	fill_path(int direction, char *path, t_mlx *m)
{
	if (!m->t[direction].path)
	{
		m->t[direction].path = ft_strdup(path);
		return ;
	}
	else
		error_mess("double type identifier\n");
}

void	check_ident(char **line, t_mlx *m, int *sky, int *floor)
{
	if (!ft_strcmp("SO", line[0]) || !ft_strcmp("NO", line[0])
		|| !ft_strcmp("WE", line[0]) || !ft_strcmp("EA", line[0]))
		check_textures(line, m);
	else if (!ft_strcmp("F", line[0]))
	{
		if (*floor != -1)
			error_mess("double type identifier\n");
		*floor = TRUE;
		return ;
	}
	else if (!ft_strcmp("C", line[0]))
	{
		if (*sky != -1)
			error_mess("double type identifier\n");
		*sky = TRUE;
		return ;
	}
	else if (!empty_line(line))
		error_mess("undefined identifier\n");
}
