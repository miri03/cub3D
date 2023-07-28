/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ident_uti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:24:16 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 14:15:36 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	start_pos(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

char	put_line_uti(char c)
{
	if (c == 'X')
		error_mess("Wrong character\n");
	return (c);
}

void	check_textures(char **line, t_mlx *m)
{
	if (tab_len(line) != 2)
		error_mess("Error texture path\n");
	if (!ft_strcmp("SO", line[0]))
		fill_path(SOUTH, line[1], m);
	else if (!ft_strcmp("NO", line[0]))
		fill_path(NORTH, line[1], m);
	else if (!ft_strcmp("WE", line[0]))
		fill_path(WEST, line[1], m);
	else if (!ft_strcmp("EA", line[0]))
		fill_path(EAST, line[1], m);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	empty_line(char **line)
{
	int	i;
	int	c;

	c = 0;
	while (line[c])
	{
		i = 0;
		while (line[c][i] && ((line[c][i] >= 9 && line[c][i] <= 13)
				|| line[c][i] == 32))
			i++;
		if (line[c][i])
			return (0);
		c++;
	}
	return (1);
}
