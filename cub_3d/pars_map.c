/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:42:36 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 16:44:20 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	first_last(char **map, t_mlx *m)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == 'X' || map[0][i] == '1')
			i++;
		else
			error_mess("first line not only walls\n");
	}
	i = 0;
	while (map[m->map.y_elements_nb - 1][i])
	{
		if (map[m->map.y_elements_nb - 1][i] == 'X' || map[m->map.y_elements_nb
			- 1][i] == '1' || map[m->map.y_elements_nb - 1][i] == '\n')
			i++;
		else
			error_mess("ERROR last line\n");
	}
}

void	get_angle(char c, t_mlx *m)
{
	if (m->p.angle != -1)
		error_mess("Multiple players\n");
	if (c == 'N')
		m->p.angle = 270 * (M_PI / 180);
	else if (c == 'W')
		m->p.angle = 180 * (M_PI / 180);
	else if (c == 'E')
		m->p.angle = 0 * (M_PI / 180);
	else if (c == 'S')
		m->p.angle = 90 * (M_PI / 180);
}

void	pars_character(char *line, t_mlx *m)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'X'
			|| start_pos(line[i]))
		{
			if (start_pos(line[i]))
				get_angle(line[i], m);
			i++;
		}
		else
			error_mess("Wrong character\n");
	}
}

void	valid_line(char *line, t_mlx *m, int index)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == 'X')
		i++;
	if (line[i] && line[i] != '1')
		error_mess("Does not start with a wall\n");
	i++;
	while (line[i])
	{
		if (line[i] == '0' && (m->map.map[index - 1][i] == 'X'
			|| m->map.map[index + 1][i] == 'X'))
			error_mess("not surrounded by walls\n");
		if (line[i] == '0' && (line[i - 1] == 'X' || line[i + 1] == 'X'))
			error_mess("Not surrounded by walls\n");
		i++;
	}
}

void	pars_map(char **map, t_mlx *m)
{
	int	i;

	i = 1;
	first_last(map, m);
	while (map[i] && i < m->map.y_elements_nb - 1)
	{
		pars_character(map[i], m);
		valid_line(map[i], m, i);
		i++;
	}
	if (m->p.angle == -1)
		error_mess("No player in the map\n");
}
