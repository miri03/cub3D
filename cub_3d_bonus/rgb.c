/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:12:18 by meharit           #+#    #+#             */
/*   Updated: 2023/08/01 19:46:30 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	pars_color(char *line, t_mlx *m, int ident)
{
	if (ident)
		m->map.sky_color = check_rgb(line);
	else
		m->map.floor_color = check_rgb(line);
}

void	pars_rgb(char *rgb)
{
	int	i;

	i = 0;
	if (rgb[i] == '-' || rgb[i] == '+')
		i++;
	while (rgb[i] && ft_isdigit(rgb[i]))
		i++;
	if (rgb[i])
		error_mess("RGB NOT DIGIT\n");
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_rgb_uti(char **rgb, int i)
{
	char	*n_rgb;
	char	**tt;
	int		j;

	while (rgb[i])
	{
		j = 0;
		if (i == 0)
			check_id(rgb[i], &j);
		while (i && (rgb[i][j] && (rgb[i][j] == ' ' || rgb[i][j] == '\t')))
			j++;
		if (rgb[i][j])
		{
			n_rgb = ft_strdup(&rgb[i][j]);
			free(rgb[i]);
			rgb[i] = n_rgb;
		}
		tt = ft_space_split(rgb[i], ' ', '\t');
		if (tab_len(tt) != 1)
			error_mess("Space in RGB\n");
		free(rgb[i]);
		rgb[i] = ft_strdup(tt[0]);
		free_tab(tt);
		i++;
	}
}

int	check_rgb(char *str)
{
	int				i;
	char			**rgb;
	unsigned long	color[3];

	i = 0;
	comma(str);
	if (str[ft_strlen(str) - 2] == ',')
		error_mess("RGB invalid\n");
	rgb = ft_space_split(str, ',', '\n');
	check_rgb_uti(rgb, i);
	while (rgb[i])
	{
		pars_rgb(rgb[i]);
		if (ft_strlen(rgb[i]) > 4)
			error_mess("RGB invalid\n");
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
			error_mess("RGB invalid\n");
		i++;
	}
	free_tab(rgb);
	return (color[0] * 256 * 256 + color[1] * 256 + color[2]);
}
